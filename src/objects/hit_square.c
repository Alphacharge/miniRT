/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:50:50 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/23 18:50:57 by humbi            ###   ########.fr       */
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
//maybe this all replace with formula distance point line
	//intersectionpoint on square
	inter = point_at(*ray, t);
	//vector from square origin to intersection
	diff = subtract_vector(inter, obj->origin);
	//now virtuell plane through intersectionpoint with normalvector of the X vector of the square
	//we will get back t for the normal vector thats the Y length of diff, lying on the virtuell plane
	//length diff is the hypothenuse, X we can calculate, normal to the virtuell plane.
	ortho = scalar_vector(obj->vector2, unit_vector(diff));
	if (ortho == 0)
		return (false);
	pln_d = scalar_vector(inter, obj->vector2);
	dis = scalar_vector(obj->vector2, obj->origin);
	y = (pln_d - dis) / ortho;
//is equal y
	x = sqrt(length_squared(diff) - pow(y, 2));
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
