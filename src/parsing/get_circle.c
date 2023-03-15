/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:15:24 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/15 12:09:34 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_circle(t_obj *obj, t_vec vec)
{
	t_obj *obj_c;
	t_obj *tmp;
	t_vec v;

	obj_c = ft_calloc(1, sizeof(t_obj));
	if (obj && obj_c && obj->radius && obj->hei_fov && obj->color && obj->vector)
	{
		obj_c->type = CIRCLE;
		v = add_vector(*obj->coord, factor_mult_vector(vec, obj->hei_fov / 2));
		obj_c->coord = new_vector(v.x, v.y, v.z);
		obj_c->vector = new_vector(vec.x, vec.y, vec.z);
		obj_c->radius = obj->radius;
		obj_c->color = new_vector(obj->color->x, obj->color->y, obj->color->z);
		tmp = obj;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = obj_c;
	}
	else
		print_syntax_error(obj_c, "Circle");
}
