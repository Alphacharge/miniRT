/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:54:00 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/04 16:13:42 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	hook(mlx_t* mlx, void (*f)(void*), void* param)
{
	t_cam	*cam;

	cam = param;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		cam->origin.x -= 10;
		draw_image(cam->img, cam, obj);
	}
}
