/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtx_host.cu                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:00:00 by rbetz             #+#    #+#             */
/*   Updated: 2026/05/22 10:00:00 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cuda_runtime.h>
#include <time.h>

/* 'new' is used as parameter name in libft.h but is a C++ keyword */
#define new new_node
extern "C" {
#include "miniRT.h"
#include "rtx.h"
}
#undef new

/* Declared in rtx_kernel.cu */
extern "C"
__global__ void render_kernel(t_gpu_obj *objs, int num_objs,
	t_gpu_cam *cam, t_gpu_config *cfg, float *accum, float *pixels,
	int sample_count, unsigned int base_seed);

extern "C"
__global__ void pixels_to_rgba_kernel(float *pixels, unsigned int *rgba,
	int num_pixels);

#define CUDA_CHECK(call) do { \
	cudaError_t err = call; \
	if (err != cudaSuccess) { \
		fprintf(stderr, "CUDA error at %s:%d: %s\n", \
			__FILE__, __LINE__, cudaGetErrorString(err)); \
		return 1; \
	} \
} while(0)

extern "C" int	cuda_init(t_data *data, t_cuda_ctx **ctx_out)
{
	t_cuda_ctx		*ctx;
	t_gpu_obj		*h_objs;
	t_gpu_cam		h_cam;
	t_gpu_config	h_cfg;
	int				num_pixels;

	/* Check for CUDA devices */
	int device_count = 0;
	cudaError_t err = cudaGetDeviceCount(&device_count);
	if (err != cudaSuccess || device_count == 0)
	{
		fprintf(stderr, "CUDA: No CUDA-capable device detected.\n");
		fprintf(stderr, "CUDA: Make sure NVIDIA drivers are installed.\n");
		fprintf(stderr, "CUDA: Run 'nvidia-smi' to check GPU status.\n");
		return 1;
	}

	/* Print GPU info */
	int device;
	cudaDeviceProp prop;
	cudaGetDevice(&device);
	cudaGetDeviceProperties(&prop, device);
	printf("CUDA: Using %s (%d SMs, %zu MB)\n",
		prop.name, prop.multiProcessorCount,
		prop.totalGlobalMem / (1024 * 1024));

	ctx = (t_cuda_ctx *)calloc(1, sizeof(t_cuda_ctx));
	if (!ctx)
		return 1;

	/* Convert objects to flat array */
	h_objs = convert_objects(data->obj, &ctx->num_objects);
	if (!h_objs)
		return (free(ctx), 1);

	/* Convert camera and config */
	convert_camera(&h_cam, data->cam);
	convert_config(&h_cfg, data);

	num_pixels = data->width * data->height;

	/* Allocate device memory */
	CUDA_CHECK(cudaMalloc(&ctx->d_objects,
		sizeof(t_gpu_obj) * ctx->num_objects));
	CUDA_CHECK(cudaMalloc(&ctx->d_cam, sizeof(t_gpu_cam)));
	CUDA_CHECK(cudaMalloc(&ctx->d_config, sizeof(t_gpu_config)));
	CUDA_CHECK(cudaMalloc(&ctx->d_pixels, sizeof(float) * num_pixels * 3));
	CUDA_CHECK(cudaMalloc(&ctx->d_accum, sizeof(float) * num_pixels * 3));
	CUDA_CHECK(cudaMalloc(&ctx->d_rgba, sizeof(unsigned int) * num_pixels));

	/* Copy data to device */
	CUDA_CHECK(cudaMemcpy(ctx->d_objects, h_objs,
		sizeof(t_gpu_obj) * ctx->num_objects, cudaMemcpyHostToDevice));
	CUDA_CHECK(cudaMemcpy(ctx->d_cam, &h_cam,
		sizeof(t_gpu_cam), cudaMemcpyHostToDevice));
	CUDA_CHECK(cudaMemcpy(ctx->d_config, &h_cfg,
		sizeof(t_gpu_config), cudaMemcpyHostToDevice));

	/* Zero accumulation buffer */
	CUDA_CHECK(cudaMemset(ctx->d_accum, 0, sizeof(float) * num_pixels * 3));

	ctx->sample_count = 0;
	free(h_objs);
	*ctx_out = ctx;
	printf("CUDA: Initialized (%d objects, %dx%d)\n",
		ctx->num_objects, data->width, data->height);
	return 0;
}

extern "C" int	cuda_render(t_cuda_ctx *ctx, t_data *data)
{
	int		num_pixels;
	dim3	block(16, 16);
	dim3	grid;

	grid.x = (data->width + block.x - 1) / block.x;
	grid.y = (data->height + block.y - 1) / block.y;
	num_pixels = data->width * data->height;

	unsigned int base_seed = (unsigned int)time(NULL) + ctx->sample_count * 7919;

	/* Launch render kernel */
	render_kernel<<<grid, block>>>(
		ctx->d_objects, ctx->num_objects,
		ctx->d_cam, ctx->d_config,
		ctx->d_accum, ctx->d_pixels,
		ctx->sample_count, base_seed
	);

	/* Launch RGBA conversion kernel on GPU (no CPU pixel loop!) */
	int rgba_threads = 256;
	int rgba_blocks = (num_pixels + rgba_threads - 1) / rgba_threads;
	pixels_to_rgba_kernel<<<rgba_blocks, rgba_threads>>>(
		ctx->d_pixels, ctx->d_rgba, num_pixels
	);

	CUDA_CHECK(cudaGetLastError());
	CUDA_CHECK(cudaDeviceSynchronize());

	/* Copy RGBA directly into MLX image buffer */
	CUDA_CHECK(cudaMemcpy(data->img->pixels, ctx->d_rgba,
		sizeof(unsigned int) * num_pixels, cudaMemcpyDeviceToHost));

	ctx->sample_count++;
	if (ctx->sample_count % 25 == 0)
		printf("CUDA: Sample %d done\n", ctx->sample_count);
	return 0;
}

extern "C" void	cuda_cleanup(t_cuda_ctx *ctx)
{
	if (!ctx)
		return;
	if (ctx->d_objects)
		cudaFree(ctx->d_objects);
	if (ctx->d_cam)
		cudaFree(ctx->d_cam);
	if (ctx->d_config)
		cudaFree(ctx->d_config);
	if (ctx->d_pixels)
		cudaFree(ctx->d_pixels);
	if (ctx->d_accum)
		cudaFree(ctx->d_accum);
	if (ctx->d_rgba)
		cudaFree(ctx->d_rgba);
	free(ctx);
}

/*
** Main CUDA render loop - replaces thread-based rendering.
** Called from mlx loop hook for progressive rendering.
*/
static t_cuda_ctx	*g_cuda_ctx = NULL;

static void	cuda_loop_hook(void *param)
{
	t_data	*data = (t_data *)param;

	if (!g_cuda_ctx)
		return;
	if (SAMPLES > 0 && g_cuda_ctx->sample_count >= SAMPLES)
		return;
	cuda_render(g_cuda_ctx, data);
}

extern "C" int	cuda_render_loop(t_data *data)
{
	if (cuda_init(data, &g_cuda_ctx) != 0)
	{
		fprintf(stderr, "CUDA: Failed to initialize\n");
		return 1;
	}
	printf("CUDA: Starting GPU render loop\n");
	mlx_loop_hook(data->mlx, cuda_loop_hook, data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	cuda_cleanup(g_cuda_ctx);
	g_cuda_ctx = NULL;
	return 0;
}
