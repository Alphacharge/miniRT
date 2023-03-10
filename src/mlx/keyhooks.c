/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:54:00 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/10 09:45:18 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_data	*data;
	data = param;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		data->cam->origin.x += STEPSIZE;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		data->cam->origin.x -= STEPSIZE;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		data->cam->origin.y -= STEPSIZE;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		data->cam->origin.y += STEPSIZE;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		data->cam->origin.z += STEPSIZE;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		data->cam->origin.z -= STEPSIZE;
	if (keydata.key != MLX_KEY_ESCAPE)
		draw_image(data->img, data->cam, data->obj);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}
