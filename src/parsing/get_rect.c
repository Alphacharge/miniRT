/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:12:54 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/28 16:05:32 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_rect(t_obj *obj, char **split)
{
	char	**tmp;

	if (obj && split && split[1] && split[2] && split[3] && split[4] && split[5] && split[6] && split[7])
	{
		pre_check(obj, "Rectangle Position", 1, split[1]);
		pre_check(obj, "Rectangle Length Vector", 1, split[2]);
		pre_check(obj, "Rectangle Length", 2, split[3]);
		pre_check(obj, "Rectangle Width Vector", 1, split[4]);
		pre_check(obj, "Rectangle Width", 2, split[5]);
		pre_check(obj, "Rectangle Height", 2, split[6]);
		pre_check(obj, "Rectangle Color", 1, split[7]);
		if (obj->type != -1)
			obj->type = RECT;
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
		obj->radius = ft_atof(split[3]);
		tmp = ft_split_p(split[4], ',');
		if (vector_check(ORI2, tmp, obj->type))
			obj->vector2 = unit_vector(new_vector(ft_atof(tmp[0]), \
			ft_atof(tmp[1]), ft_atof(tmp[2])));
		free(tmp);
		obj->width = ft_atof(split[5]);
		obj->hei_fov = ft_atof(split[6]);
		tmp = ft_split_p(split[7], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->color = new_vector(ft_atof(tmp[0]) / 255.0, \
			ft_atof(tmp[1]) / 255.0, ft_atof(tmp[2]) / 255.0);
		free(tmp);
		get_square(obj, 1);
		get_square(obj, -1);
		get_square(obj, 2);
		get_square(obj, -2);
		get_square(obj, 3);
		get_square(obj, -3);
	}
	else
		print_syntax_error(obj, "Rectangle");
}
