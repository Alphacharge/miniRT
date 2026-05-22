/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:00:00 by rbetz             #+#    #+#             */
/*   Updated: 2026/05/13 10:00:00 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTX_H
# define RTX_H

# ifdef __cplusplus
extern "C" {
# endif

/*GPU-friendly flat object structure (no pointers/linked lists)*/
typedef struct s_gpu_obj
{
	int		type;
	float	radius;
	float	width;
	float	hei_fov;
	float	origin[3];
	float	vector[3];
	float	vector2[3];
	float	color[3];
}			t_gpu_obj;

/*GPU camera parameters*/
typedef struct s_gpu_cam
{
	float	focal_length;
	float	origin[3];
	float	direction[3];
	float	horizontal[3];
	float	vertical[3];
	float	upper_left_corner[3];
}			t_gpu_cam;

/*GPU render configuration*/
typedef struct s_gpu_config
{
	int		width;
	int		height;
	int		max_depth;
	int		soft_shadow;
	int		bounces;
	int		sky;
	float	albedo;
	float	light_factor;
	float	ambient[3];
}			t_gpu_config;

/*Host-side CUDA context*/
typedef struct s_cuda_ctx
{
	t_gpu_obj		*d_objects;
	t_gpu_cam		*d_cam;
	t_gpu_config	*d_config;
	float			*d_pixels;
	float			*d_accum;
	unsigned int	*d_rgba;
	int				num_objects;
	int				sample_count;
}					t_cuda_ctx;

/*Forward declaration for t_data and t_obj from miniRT*/
struct s_data;
struct s_obj;
struct s_camera;

/*Conversion functions (rtx_convert.c)*/
t_gpu_obj	*convert_objects(struct s_obj *obj, int *num_objects);
void		convert_camera(t_gpu_cam *gpu_cam, struct s_camera *cam);
void		convert_config(t_gpu_config *cfg, struct s_data *data);

/*Host interface functions (callable from C)*/
int		cuda_init(struct s_data *data, t_cuda_ctx **ctx);
int		cuda_render(t_cuda_ctx *ctx, struct s_data *data);
void	cuda_cleanup(t_cuda_ctx *ctx);
int		cuda_render_loop(struct s_data *data);

# ifdef __cplusplus
}
# endif

#endif
