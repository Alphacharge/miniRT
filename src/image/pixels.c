/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:36:08 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/27 21:02:49 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	draw_image(mlx_image_t *img, t_cam *cam)
{
	int			col;
	int			row;
	t_ray		*ray;

	col = 0;
	row = 0;
	ray = new_ray(cam->origin, NULL);
	printf("Image size: %ix%i\n", img->width, img->height);

	//shoot a ray through camera origin and every pixel (image plane)
	while (row < (int)img->height)
	{
		while (col < (int)img->width)
		{
			ray->direction = new_vector(cam->upper_left_corner->x + col, cam->upper_left_corner->y + row, cam->focal_length * -1);
			//find the nearest object that ray hits (t closest to 0)
			//determine direction
			//determine shading
			mlx_put_pixel(img, col, row, ray_color(ray));
			ray->direction = ft_free(ray->direction);
			col++;
		}
		col = 0;
		row++;
	}
	ft_free(ray);
	printf("Image rendered.\n");
	return (0);
}
