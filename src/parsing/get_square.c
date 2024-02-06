/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:15:24 by rbetz             #+#    #+#             */
/*   Updated: 2023/08/30 15:40:32 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	decide_len_hei(t_obj *obj, int dir, t_obj *var)
{
	if (obj && (dir == 1 || dir == -1))
	{
		var->radius = obj->width;
		var->hei_fov = obj->hei_fov;
		var->width = obj->radius;
	}
	else if (obj && (dir == 2 || dir == -2))
	{
		var->radius = obj->radius;
		var->hei_fov = obj->hei_fov;
		var->width = obj->width;
	}
	else if (obj && (dir == 3 || dir == -3))
	{
		var->radius = obj->radius;
		var->hei_fov = obj->width;
		var->width = obj->hei_fov;
	}
}

static void	decide_vectors(t_obj *obj, int dir, t_obj *var)
{
	if (obj && (dir == 1 || dir == -1))
	{
		var->vector = obj->vector;
		var->vector2 = obj->vector2;
	}
	else if (obj && (dir == 2 || dir == -2))
	{
		var->vector = obj->vector2;
		var->vector2 = obj->vector;
	}
	else if (obj && (dir == 3 || dir == -3))
	{
		var->vector = cross_vector(obj->vector, obj->vector2);
		var->vector2 = obj->vector;
	}
	if (dir < 0)
		var->vector = invert_vector(var->vector);
	decide_len_hei(obj, dir, var);
}

void	get_square(t_obj *obj, t_obj *obj_r, int dir)
{
	t_obj	var;

	ft_memset(&var, 0, sizeof(t_obj));
	if (obj && obj_r)
	{
		obj_r->type = SQUA;
		decide_vectors(obj, dir, &var);
		obj_r->origin = add_vector(obj->origin, \
					factor_mult_vector(var.vector, var.width / 2));
		obj_r->vector = unit_vector(\
					subtract_vector(obj->origin, obj->origin));
		obj_r->vector2 = unit_vector(var.vector2);
		obj_r->radius = var.radius;
		obj_r->width = var.hei_fov;
		obj_r->reflection = var.reflection;
		obj_r->color = new_vector(obj->color.x, obj->color.y, obj->color.z);
	}
	else
		print_syntax_error(obj_r, "Square");
}
