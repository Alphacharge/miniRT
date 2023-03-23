/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:15:24 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/23 17:27:02 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	decide_vectors(t_obj *obj, int dir, t_vec *v, t_vec *w)
{
	if (obj && (dir == 1 || dir == -1))
	{
		*v = obj->vector;
		*w = obj->vector2;
	}
	else if (obj && (dir == 2 || dir == -2))
	{
		*v = obj->vector2;
		*w = obj->vector;
	}
	else if (obj && (dir == 3 || dir == -3))
	{
		*v = cross_vector(obj->vector, obj->vector2);
		*w = obj->vector;
	}
	if (dir < 0)
		*v = invert_vector(*v);
}

static void	decide_len_hei(t_obj *obj, int dir, double *len, double *hei)
{
	if (obj && (dir == 1 || dir == -1))
	{
		*len = obj->width;
		*hei = obj->hei_fov;
	}
	else if (obj && (dir == 2 || dir == -2))
	{
		*len = obj->radius;
		*hei = obj->hei_fov;
	}
	else if (obj && (dir == 3 || dir == -3))
	{
		*len = obj->radius;
		*hei = obj->width;
	}
}

void	get_square(t_obj *obj, int dir)
{
	t_obj	*obj_c;
	t_obj	*tmp;
	t_vec	v;
	t_vec	w;
	double	len;
	double	hei;

	len = 0;
	hei = 0;
	obj_c = ft_calloc(1, sizeof(t_obj));
	if (obj && obj_c)
	{
		obj_c->type = SQUA;
		decide_vectors(obj, dir, &v, &w);
		decide_len_hei(obj, dir, &len, &hei);
		v = add_vector(obj->origin, factor_mult_vector(v, len / 2));
		obj_c->origin = new_vector(v.x, v.y, v.z);
		obj_c->vector = unit_vector(v);
		obj_c->vector2 = unit_vector(w);
		obj_c->radius = len;
		obj_c->width = hei;
		obj_c->color = new_vector(obj->color.x, obj->color.y, obj->color.z);
		tmp = obj;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = obj_c;
	}
	else
		print_syntax_error(obj_c, "Square");
}
