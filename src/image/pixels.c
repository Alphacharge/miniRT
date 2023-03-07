/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:36:08 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/06 19:01:27 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	put_pixel(mlx_image_t *img, int x, int y, uint32_t rgba)
{
	mlx_put_pixel(img, x, y, gamma_correction(rgba));
	// mlx_put_pixel(img, x, y, rgba);
}

int	draw_image(mlx_image_t *img, t_cam *cam, t_obj *obj)
{
	int			col;
	int			row;
	t_ray		ray;

	col = 0;
	row = 0;
	printf("Image size: %ix%i\n", img->width, img->height);
	ray = new_ray();
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
	ray.direction.z = cam->focal_length * -1;
	while (row < (int)img->height)
	{
		while (col < (int)img->width)
		{
			//if camera can have different position from origin, these formulas need to be updated
			ray.direction.x = cam->upper_left_corner->x + col;
			ray.direction.y = cam->upper_left_corner->y + row;
			ray.closest_t = T_MAX;
			put_pixel(img, col, row, ray_color(ray, obj, MAX_DEPTH));
			col++;
		}
		col = 0;
		row++;
	}
	printf("Image rendered.\n");
	return (0);
}
