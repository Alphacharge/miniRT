/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:28:38 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/21 11:17:07 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec	calc_corner(t_cam *cam)
{
	t_vec	corner;

	corner = factor_mult_vector(cam->horizontal, -0.5);
	corner = add_vector(corner, factor_mult_vector(cam->vertical, -0.5));
	corner = add_vector(corner, \
			factor_mult_vector(cam->direction, cam->focal_length));
	corner = subtract_vector(corner, cam->origin);
	return (corner);
}
t_cam	*setup_cam(t_obj	*obj, int width, int height)
{
	t_cam	*cam;
	t_vec	down;

	down = new_vector(0, 1, 0);
	cam = ft_calloc(1, sizeof(t_cam));
	if (cam == NULL)
		return (error_message(13), NULL);
	while (obj && obj->type != CAM)
		obj = obj->next;
	if (obj == NULL)
		return (error_message(14), ft_free(cam), NULL);
	cam->origin = obj->origin;
	cam->focal_length = width / (2 * tan(obj->hei_fov / 2));
	cam->direction = unit_vector(obj->vector);
	cam->horizontal = unit_vector(cross_vector(down, cam->direction));
	cam->horizontal = factor_mult_vector(cam->horizontal, width);
	cam->vertical = unit_vector(cross_vector(cam->direction, cam->horizontal));
	cam->vertical = factor_mult_vector(cam->vertical, height);
	cam->upper_left_corner = calc_corner(cam);
	cam->horizontal = unit_vector(cam->horizontal);
	cam->vertical = unit_vector(cam->vertical);
	return (cam);
}
