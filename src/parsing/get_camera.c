/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:12:49 by rbetz             #+#    #+#             */
/*   Updated: 2023/04/03 10:46:28 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_cam(t_obj *obj, char **split)
{
	if (obj && split && split[1] && split[2] && split[3])
	{
		pre_check(obj, "Camera Position", 1, split[1]);
		pre_check(obj, "Camera Vector", 1, split[2]);
		pre_check(obj, "Camera FOV", 3, split[3]);
		if (obj->type != -1)
			obj->type = CAM;
		obj->origin = insert_pos_vec(split[1], obj->type, POS);
		obj->vector = unit_vector(insert_pos_vec(split[2], obj->type, ORI));
		obj->hei_fov = ft_atof(split[3]);
		if (invalid_vector(obj->origin) || invalid_vector(obj->vector) || \
			obj->hei_fov > 180.0 || obj->hei_fov <= 0.0)
		{
			printf("Camera Error\n");
			obj->type = -1;
		}
		obj->hei_fov = obj->hei_fov * M_PI / 180;
		obj->color = new_vector(0, 0, 0);
	}
	else
		print_syntax_error(obj, "Camera");
}
