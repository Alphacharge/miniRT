/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:50:50 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/27 19:18:18 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_square(t_ray *ray, t_obj *obj)
{
	double	ortho;
	double	pln_d;
	double	dis;
	double	t;
	double	x;
	double	y;
	t_vec	diff;
	t_vec	inter;

	ortho = scalar_vector(obj->vector, ray->direction);
	if (ortho == 0)
		return (false);
	pln_d = scalar_vector(obj->origin, obj->vector);
	dis = scalar_vector(obj->vector, ray->origin);
	t = (pln_d - dis) / ortho;
	if (t < T_MIN || t > T_MAX)
		return (false);
	//intersectionpoint on square
	inter = point_at(*ray, t);
	//vector from square origin to intersection
	diff = subtract_vector(inter, obj->origin);
	y = length_vector(cross_vector(diff, obj->vector2)) / length_vector(obj->vector2);
	x = length_vector(subtract_vector(diff, cross_vector(diff, obj->vector2)));	
	if (x < 0)
		x = x * -1;
	if (y < 0)
		y = y * -1;
	if (x > obj->radius / 2 || y > obj->width / 2)
		return (false);
	if (t < ray->closest_t)
	{
		ray->closest_object = obj;
		ray->closest_t = t;
		ray->normal = unit_vector(obj->vector);
		return (true);
	}
	return (false);
}
