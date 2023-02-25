/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:36:08 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/25 19:55:03 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	draw_image(mlx_image_t *img, t_cam *cam)
{
	uint32_t	col;
	uint32_t	row;
	uint32_t	color;
	t_ray		*ray;

	col = 0;
	row = 0;
	color = 0xFF000000 | 0x00FF0000 | 0x00001100 | 0x000000FF;
	printf("Image size: %ix%i\n", img->width, img->height);
	while (row < img->height)
	{
		while (col < img->width)
		{
			//problem: u and v are relative while col and row are absolute pixels
			ray = new_ray(cam->origin, subtract_vector(add_vector(add_vector(cam->lower_left_corner, factor_mult_vector(cam->horizontal, row)), factor_mult_vector(cam->vertical, col)), cam->origin));
			mlx_put_pixel(img, col, row, ray_color(ray));
			col++;
		}
		col = 0;
		row++;
	}
	printf("Image rendered.\n");
	return (0);
}
