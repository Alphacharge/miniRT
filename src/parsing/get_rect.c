/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:12:54 by rbetz             #+#    #+#             */
/*   Updated: 2023/04/03 10:46:43 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rect_check(t_obj *obj, char **split)
{
	if (obj && split && split[1] && split[2] && split[3] \
		&& split[4] && split[5] && split[6] && split[7])
	{
		pre_check(obj, "Rectangle Position", 1, split[1]);
		pre_check(obj, "Rectangle Length Vector", 1, split[2]);
		pre_check(obj, "Rectangle Length", 2, split[3]);
		pre_check(obj, "Rectangle Width Vector", 1, split[4]);
		pre_check(obj, "Rectangle Width", 2, split[5]);
		pre_check(obj, "Rectangle Height", 2, split[6]);
		pre_check(obj, "Rectangle Color", 1, split[7]);
	}
}

void	create_squares(t_obj *obj)
{
	get_square(obj, 1);
	get_square(obj, -1);
	get_square(obj, 2);
	get_square(obj, -2);
	get_square(obj, 3);
	get_square(obj, -3);
}

void	get_rect(t_obj *obj, char **split)
{
	if (obj && split && split[1] && split[2] && split[3] && split[4] \
		&& split[5] && split[6] && split[7])
	{
		rect_check(obj, split);
		if (obj->type != -1)
			obj->type = RECT;
		obj->origin = insert_pos_vec(split[1], obj->type, POS);
		obj->vector = unit_vector(insert_pos_vec(split[2], obj->type, ORI));
		obj->radius = ft_atof(split[3]);
		obj->vector2 = unit_vector(insert_pos_vec(split[4], obj->type, ORI2));
		obj->width = ft_atof(split[5]);
		obj->hei_fov = ft_atof(split[6]);
		obj->color = insert_color(split[7], obj->type);
		if (invalid_vector(obj->origin) || invalid_vector(obj->vector) \
			|| invalid_vector(obj->vector2) || invalid_color(obj->color))
		{
			printf("Rectangle Error\n");
			obj->type = -1;
			return ;
		}
		create_squares(obj);
	}
	else
		print_syntax_error(obj, "Rectangle");
}
