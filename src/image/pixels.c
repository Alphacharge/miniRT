/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:36:08 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/17 15:15:42 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	put_pixel(mlx_image_t *img, int x, int y, t_vec color)
{
	mlx_put_pixel(img, x, y, gamma_correction(color));
}

t_ray	*cam_ray(t_cam *cam)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	if (ray == NULL)
		return (NULL);
	ray->origin = cam->origin;
	ray->closest_t = T_MAX;
	ray->closest_object = NULL;
	return(ray);
}

t_ray	randomize_ray(t_ray *ray, t_cam *cam, int col, int row)
{
	double	x;
	double	y;

	x = (double)col + random_double();
	y = (double)row + random_double();
	ray->direction = factor_mult_vector(cam->horizontal, x);
	ray->direction = add_vector(ray->direction, factor_mult_vector(cam->vertical, y));
	ray->direction = unit_vector(add_vector(cam->upper_left_corner, ray->direction));
	return (*ray);
}

t_vec	*get_ambient_lighting(t_obj *obj)
{
	t_vec	ambient;
	t_vec	*allocate;

	ambient.x = 0;
	ambient.y = 0;
	ambient.z = 0;
	while (obj != NULL)
	{
		if (obj->type == AMBI)
			ambient = add_vector(ambient, factor_mult_vector(obj->color, obj->intensity));
		obj = obj->next;
	}
	allocate = ft_calloc(1, sizeof(t_vec));
	if (allocate == NULL)
		return (NULL);
	allocate->x = ambient.x;
	allocate->y = ambient.y;
	allocate->z = ambient.z;
	return (allocate);
}

int	draw_image(mlx_image_t *img, t_cam *cam, t_obj *obj)
{
	int			col;
	int			row;
	t_ray		*ray;
	t_vec		color;
	t_vec		color_new;
	int			i;

	row = 0;
	ray = cam_ray(cam);
	ray->ambient_light = get_ambient_lighting(obj);
	printf("Image size: %ix%i\n", HEIGHT, WIDTH);
	while (row < HEIGHT)
	{
		col = 0;
		while (col < WIDTH)
		{
			color = color_to_vector(0x000000FF);
			i = 0;
			while (i < SAMPLES)
			{
				ray->closest_t = T_MAX;
				ray->closest_object = NULL;
				color_new = ray_color(randomize_ray(ray, cam, col, row), obj, MAX_DEPTH);
				color = add_vector(color, color_new);
				i++;
			}
			color = factor_mult_vector(color, 1 / (double)SAMPLES);
			if (MLX == true)
				put_pixel(img, col, row, color);
			col++;
		}
		row++;
	}
	ft_free(ray->ambient_light);
	ft_free(ray);
	printf("Image rendered.\n");
	return (0);
}
