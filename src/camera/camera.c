/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:28:38 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/25 17:43:33 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_cam	*setup_camera(int width, int height)
{
	t_cam	*cam;

	cam = ft_calloc(1, sizeof(t_cam));
	if (cam == NULL)
		return (0);
	cam->focal_length = 1.0;
	cam->origin = new_vector(0, 0, 0);
	cam->horizontal = new_vector(width, 0, 0);
	cam->vertical = new_vector(0, height, 0);
	cam->lower_left_corner = subtract_vector(cam->origin, factor_div_vector(cam->horizontal, 2));
	cam->lower_left_corner = subtract_vector(cam->lower_left_corner, factor_div_vector(cam->horizontal, 2));
	cam->lower_left_corner = subtract_vector(cam->lower_left_corner, new_vector(0, 0, cam->focal_length));
	return (cam);
}
