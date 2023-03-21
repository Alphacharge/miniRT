/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:54:00 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/21 15:45:53 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	if (keydata.key == MLX_KEY_ESCAPE)
		escape(data);
}
