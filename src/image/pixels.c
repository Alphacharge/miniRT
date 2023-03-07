/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:36:08 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/07 18:08:08 by fkernbac         ###   ########.fr       */
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
	t_vec		image_plane;

	col = 0;
	row = 0;
	printf("Image size: %ix%i\n", img->width, img->height);
	ray = new_ray();
	ray.origin = cam->origin;
	image_plane = add_vector(cam->origin, cam->upper_left_corner);
	while (row < (int)img->height)
	{
		while (col < (int)img->width)
		{
			ray.direction = add_vector(image_plane, factor_mult_vector(cam->horizontal, col));
			ray.direction = add_vector(ray.direction, factor_mult_vector(cam->vertical, row));
			ray.direction = subtract_vector(ray.direction, cam->origin);
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
