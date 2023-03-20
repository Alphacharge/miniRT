/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:54:00 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/20 14:36:44 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// static void	turn_cam(mlx_t *mlx, t_cam *cam, int axis, int dir)
// {
// 	double	ang;

// 	ang = 10 / M_PI * 180;
// 	print_vector(cam->direction);
// 	if (axis == 0 && dir == 0)
// 	{
// 		cam->direction.x = cos(ang) * cam->direction.x - sin(ang) * cam->direction.y;
// 		cam->direction.y = sin(ang) * cam->direction.x + cos(ang) * cam->direction.y;
// 	}
// 	if (axis == 0 && dir == 1)
// 	{
// 		cam->direction.x = -cos(ang) * cam->direction.x + sin(ang) * cam->direction.y;
// 		cam->direction.y = +sin(ang) * cam->direction.x - cos(ang) * cam->direction.y;
// 	}
// 	if (axis == 2)
// 		cam->direction.y -= ang;
// 	if (axis == 3)
// 		cam->direction.y += ang;
// 	if (axis == 4)
// 		cam->direction.z -= ang;
// 	if (axis == 5)
// 		cam->direction.z += ang;
// 	// cam->direction = unit_vector(cam->direction);
// 	print_vector(cam->direction);
// 	update_cam(cam, mlx->width, mlx->height);
// }
void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_data	*data;
	data = param;
	if (keydata.action != MLX_RELEASE)
		return ;
	if (keydata.key == MLX_KEY_D)
		data->cam->origin.x += STEPSIZE;
	if (keydata.key == MLX_KEY_A)
		data->cam->origin.x -= STEPSIZE;
	if (keydata.key == MLX_KEY_W)
		data->cam->origin.y -= STEPSIZE;
	if (keydata.key == MLX_KEY_S)
		data->cam->origin.y += STEPSIZE;
	if (keydata.key == MLX_KEY_E)
		data->cam->origin.z += STEPSIZE;
	if (keydata.key == MLX_KEY_Q)
		data->cam->origin.z -= STEPSIZE;
	// if (keydata.key == MLX_KEY_LEFT)
	// 	turn_cam(data->mlx, data->cam, 0, 0);
	// if (keydata.key == MLX_KEY_RIGHT)
	// 	turn_cam(data->mlx, data->cam, 0, 1);
	// if (keydata.key == MLX_KEY_UP)
	// 	turn_cam(data->mlx, data->cam, 1, 0);
	// if (keydata.key == MLX_KEY_DOWN)
	// 	turn_cam(data->mlx, data->cam, 1, 1);
	// if (keydata.key == MLX_KEY_PAGE_UP)
	// 	turn_cam(data->mlx, data->cam, 2, 0);
	// if (keydata.key == MLX_KEY_PAGE_DOWN)
	// 	turn_cam(data->mlx, data->cam, 2, 1);
	// if (keydata.key != MLX_KEY_ESCAPE)
		// draw_image(data->img, data->cam, data->obj);
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
}
