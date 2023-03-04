/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:36:08 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/04 12:49:55 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	draw_image(mlx_image_t *img, t_cam *cam)
{
	int			col;
	int			row;
	t_ray		ray;

	col = 0;
	row = 0;
	printf("Image size: %ix%i\n", img->width, img->height);
	if (cam && cam->origin)
	{
		ray.origin.x = cam->origin->x;
		ray.origin.y = cam->origin->y;
		ray.origin.z = cam->origin->z;
	}
	else
	{
		ray.origin.x = 0;
		ray.origin.y = 0;
		ray.origin.z = 0;	
	}
	ray.closest_object = NULL;
	while (row < (int)img->height)
	{
		while (col < (int)img->width)
		{
			ray.direction.x = cam->upper_left_corner->x + col;
			ray.direction.y = cam->upper_left_corner->y + row;
			ray.direction.z = cam->focal_length * -1;
			ray.closest_t = T_MAX;
			mlx_put_pixel(img, col, row, ray_color(&ray));
			col++;
		}
		col = 0;
		row++;
	}
	printf("Image rendered.\n");
	return (0);
}
