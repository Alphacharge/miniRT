/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:54:00 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/30 16:38:47 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action != MLX_RELEASE)
		return ;
	if (keydata.key == MLX_KEY_D)
		refresh_cam(data, 1);
	if (keydata.key == MLX_KEY_A)
		refresh_cam(data, 2);
	if (keydata.key == MLX_KEY_W)
		refresh_cam(data, 3);
	if (keydata.key == MLX_KEY_S)
		refresh_cam(data, 4);
	if (keydata.key == MLX_KEY_E)
		refresh_cam(data, 5);
	if (keydata.key == MLX_KEY_Q)
		refresh_cam(data, 6);
	if (keydata.key == MLX_KEY_SPACE)
		refresh_cam(data, 7);
	if (keydata.key == MLX_KEY_ESCAPE)
		escape(data);
}
