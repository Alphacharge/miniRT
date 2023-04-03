/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:12:54 by rbetz             #+#    #+#             */
/*   Updated: 2023/04/03 10:46:18 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	cyl_check(t_obj *obj, char **split)
{
	if (obj && split && split[1] && split[2] && split[3] \
		&& split[4] && split[5])
	{
		pre_check(obj, "Cylinder Position", 1, split[1]);
		pre_check(obj, "Cylinder Vector", 1, split[2]);
		pre_check(obj, "Cylinder Diameter", 2, split[3]);
		pre_check(obj, "Cylinder Height", 2, split[4]);
		pre_check(obj, "Cylinder Color", 1, split[5]);
	}
}

void	get_cyl(t_obj *obj, char **split)
{
	if (obj && split && split[1] && split[2] && split[3] \
		&& split[4] && split[5])
	{
		cyl_check(obj, split);
		if (obj->type != -1)
			obj->type = CYL;
		obj->origin = insert_pos_vec(split[1], obj->type, POS);
		obj->vector = unit_vector(insert_pos_vec(split[2], obj->type, ORI));
		obj->radius = ft_atof(split[3]) / 2.0;
		obj->hei_fov = ft_atof(split[4]);
		obj->color = insert_color(split[5], obj->type);
		if (invalid_vector(obj->origin) || invalid_vector(obj->vector) \
			|| invalid_color(obj->color) || obj->radius <= 0.0)
		{
			printf("Cylinder Error\n");
			obj->type = -1;
			return ;
		}
		get_circle(obj, obj->vector);
		get_circle(obj, invert_vector(obj->vector));
	}
	else
		print_syntax_error(obj, "Cylinder");
}
