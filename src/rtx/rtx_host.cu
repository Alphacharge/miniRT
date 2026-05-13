/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtx_host.cu                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:00:00 by rbetz             #+#    #+#             */
/*   Updated: 2026/05/13 10:00:00 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
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
	t_gpu_cam *cam, t_gpu_config *cfg, double *accum, double *pixels,
	int sample_count, unsigned int base_seed);

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
	CUDA_CHECK(cudaMalloc(&ctx->d_pixels, sizeof(double) * num_pixels * 3));
	CUDA_CHECK(cudaMalloc(&ctx->d_accum, sizeof(double) * num_pixels * 3));

	/* Copy data to device */
	CUDA_CHECK(cudaMemcpy(ctx->d_objects, h_objs,
		sizeof(t_gpu_obj) * ctx->num_objects, cudaMemcpyHostToDevice));
	CUDA_CHECK(cudaMemcpy(ctx->d_cam, &h_cam,
		sizeof(t_gpu_cam), cudaMemcpyHostToDevice));
	CUDA_CHECK(cudaMemcpy(ctx->d_config, &h_cfg,
		sizeof(t_gpu_config), cudaMemcpyHostToDevice));

	/* Zero accumulation buffer */
	CUDA_CHECK(cudaMemset(ctx->d_accum, 0, sizeof(double) * num_pixels * 3));

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
	double	*h_pixels;
	dim3	block(16, 16);
	dim3	grid;

	grid.x = (data->width + block.x - 1) / block.x;
	grid.y = (data->height + block.y - 1) / block.y;
	num_pixels = data->width * data->height;

	unsigned int base_seed = (unsigned int)time(NULL) + ctx->sample_count * 7919;

	/* Launch kernel */
	render_kernel<<<grid, block>>>(
		ctx->d_objects, ctx->num_objects,
		ctx->d_cam, ctx->d_config,
		ctx->d_accum, ctx->d_pixels,
		ctx->sample_count, base_seed
	);
	CUDA_CHECK(cudaGetLastError());
	CUDA_CHECK(cudaDeviceSynchronize());

	/* Copy pixels back */
	h_pixels = (double *)malloc(sizeof(double) * num_pixels * 3);
	if (!h_pixels)
		return 1;
	CUDA_CHECK(cudaMemcpy(h_pixels, ctx->d_pixels,
		sizeof(double) * num_pixels * 3, cudaMemcpyDeviceToHost));

	/* Write to MLX image with gamma correction */
	for (int y = 0; y < data->height; y++)
	{
		for (int x = 0; x < data->width; x++)
		{
			int idx = (y * data->width + x) * 3;
			double r = h_pixels[idx + 0];
			double g = h_pixels[idx + 1];
			double b = h_pixels[idx + 2];
			/* Clamp */
			if (r > 1.0) r = 1.0; else if (r < 0.0) r = 0.0;
			if (g > 1.0) g = 1.0; else if (g < 0.0) g = 0.0;
			if (b > 1.0) b = 1.0; else if (b < 0.0) b = 0.0;
			/* Gamma correction */
			const double gamma_val = 2.2;
			r = pow(r, 1.0 / gamma_val);
			g = pow(g, 1.0 / gamma_val);
			b = pow(b, 1.0 / gamma_val);
			int ri = (int)(r * 255.0);
			int gi = (int)(g * 255.0);
			int bi = (int)(b * 255.0);
			uint32_t color = (ri << 24) | (gi << 16) | (bi << 8) | 255;
			mlx_put_pixel(data->img, x, y, color);
		}
	}
	free(h_pixels);
	ctx->sample_count++;
	if (ctx->sample_count % 10 == 0)
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
