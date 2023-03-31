/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:15:24 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/31 10:12:56 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_circle(t_obj *obj, t_vec vec)
{
	t_obj	*obj_c;
	t_obj	*tmp;
	t_vec	v;

	v = new_vector(0, 0, 0);
	obj_c = ft_calloc(1, sizeof(t_obj));
	if (obj && obj_c)
	{
		obj_c->type = CIRCLE;
		v = add_vector(obj->origin, factor_mult_vector(vec, obj->hei_fov / 2));
		obj_c->origin = new_vector(v.x, v.y, v.z);
		obj_c->vector = unit_vector(new_vector(vec.x, vec.y, vec.z));
		obj_c->radius = obj->radius;
		obj_c->color = new_vector(obj->color.x, obj->color.y, obj->color.z);
		tmp = obj;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = obj_c;
	}
	else
		print_syntax_error(obj_c, "Circle");
}
