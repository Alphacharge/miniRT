/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:12:54 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/28 15:53:43 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_cyl(t_obj *obj, char **split)
{
	char	**tmp;

	if (obj && split && split[1] && split[2] && split[3] && split[4] && split[5])
	{
		pre_check(obj, "Cylinder Position", 1, split[1]);
		pre_check(obj, "Cylinder Vector", 1, split[2]);
		pre_check(obj, "Cylinder Diameter", 2, split[3]);
		pre_check(obj, "Cylinder Height", 2, split[4]);
		pre_check(obj, "Cylinder Color", 1, split[5]);
		if (obj->type != -1)
			obj->type = CYL;
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
		obj->radius = ft_atof(split[3]) / 2.0;
		obj->hei_fov = ft_atof(split[4]);
		tmp = ft_split_p(split[5], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->color = new_vector(ft_atof(tmp[0]) / 255.0, \
			ft_atof(tmp[1]) / 255.0, ft_atof(tmp[2]) / 255.0);
		free(tmp);
		get_circle(obj, obj->vector);
		get_circle(obj, invert_vector(obj->vector));
	}
	else
		print_syntax_error(obj, "Cylinder");
}
