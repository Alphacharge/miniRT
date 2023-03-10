/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:28:38 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/10 18:18:38 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_cam	*setup_camera(t_obj	*obj, int width, int height)
{
	t_cam	*cam;
	t_vec	down;

	down.x = 0;
	down.y = 1;
	down.z = 0;
	cam = ft_calloc(1, sizeof(t_cam));
	if (cam == NULL)
		return (NULL);
	while (obj && obj->type != CAM)
		obj = obj->next;
	if (obj == NULL)
		return (NULL); //no cam
	else
		cam->origin = *obj->coord;
	cam->focal_length = width / (2 * tan(obj->hei_fov / 2));
	cam->direction = *obj->vector;
	cam->horizontal = unit_vector(cross_vector(down, cam->direction));
	cam->horizontal = factor_mult_vector(cam->horizontal, width);
	cam->vertical = unit_vector(cross_vector(cam->direction, cam->horizontal));
	cam->vertical = factor_mult_vector(cam->vertical, height);
	cam->upper_left_corner = factor_mult_vector(cam->horizontal, -0.5);
	cam->upper_left_corner = add_vector(cam->upper_left_corner, factor_mult_vector(cam->vertical, -0.5));
	cam->upper_left_corner = add_vector(cam->upper_left_corner, factor_mult_vector(cam->direction, cam->focal_length));
	cam->upper_left_corner = subtract_vector(cam->upper_left_corner, cam->origin);
	cam->horizontal = unit_vector(cam->horizontal);	//now they have a length of 1 pixel for iterating
	cam->vertical = unit_vector(cam->vertical);
	return (cam);
}

t_cam	*delete_camera(t_cam *cam)
{
	if (cam == NULL)
		return (NULL);
	ft_free(cam);
	return (NULL);
}
