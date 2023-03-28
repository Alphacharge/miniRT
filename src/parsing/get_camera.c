/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:12:49 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/28 15:53:53 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_cam(t_obj *obj, char **split)
{
	char	**tmp;

	if (obj && split && split[1] && split[2] && split[3])
	{
		pre_check(obj, "Camera Position", 1, split[1]);
		pre_check(obj, "Camera Vector", 1, split[2]);
		pre_check(obj, "Camera FOV", 3, split[3]);
		if (obj->type != -1)
			obj->type = CAM;
		tmp = ft_split_p(split[1], ',');
		if (vector_check(POS, tmp, obj->type))
			obj->origin = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), \
			ft_atof(tmp[2]));
		free(tmp);
		tmp = ft_split_p(split[2], ',');
		if (vector_check(ORI, tmp, obj->type))
			obj->vector = unit_vector(new_vector(ft_atof(tmp[0]), \
			ft_atof(tmp[1]), ft_atof(tmp[2])));
		free(tmp);
		obj->hei_fov = ft_atof(split[3]) * M_PI / 180;
	}
	else
		print_syntax_error(obj, "Camera");
}
