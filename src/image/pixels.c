/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:36:08 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/10 18:58:49 by fkernbac         ###   ########.fr       */
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

	ray = calloc(1, sizeof(t_ray));
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
	ray->direction = add_vector(cam->upper_left_corner, ray->direction);
	return (*ray);
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
	printf("Image size: %ix%i\n", img->width, img->height);
	while (row < (int)img->height)
	{
		col = 0;
		while (col < (int)img->width)
		{
			color = color_to_vector(0x000000FF);
			i = 0;
			while (i < SAMPLES)
			{
				color_new = ray_color(randomize_ray(ray, cam, col, row), obj, MAX_DEPTH);
				color = add_vector(color, color_new);
				i++;
			}
			color = factor_mult_vector(color, 1 / (double)SAMPLES);
			put_pixel(img, col, row, color);
			col++;
		}
		row++;
	}
	printf("Image rendered.\n");
	return (0);
}
