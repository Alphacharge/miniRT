/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:28:38 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/04 12:44:49 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_cam	*setup_camera(t_obj	*obj, int width, int height)
{
	t_cam	*cam;

	cam = ft_calloc(1, sizeof(t_cam));
	if (cam == NULL)
		return (NULL);
	while (obj && obj->type != CAM)
		obj = obj->next;
	if (obj == NULL)
		return (NULL); //no cam
	else
		cam->origin = obj->coord;
	print_vector(*cam->origin);
	cam->focal_length = 200;
	cam->horizontal = new_vector(width, 0, 0);
	cam->vertical = new_vector(0, height, 0);
	cam->upper_left_corner = new_vector(width / 2 * -1, height / 2 * -1, cam->focal_length * -1);
	return (cam);
}

t_cam	*delete_camera(t_cam *cam)
{
	if (cam == NULL)
		return (NULL);
	ft_free(cam->origin);
	ft_free(cam->horizontal);
	ft_free(cam->vertical);
	ft_free(cam->upper_left_corner);
	ft_free(cam);
	return (NULL);
}
