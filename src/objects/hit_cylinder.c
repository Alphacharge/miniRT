/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:22:10 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/15 12:47:56 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_cylinder(t_ray *ray, t_obj *obj)
{
	double	abc[3];
	double	t[2];
	double	x;
	t_vec	inter;

	ray->direction = unit_vector(ray->direction);
	t_vec	d = cross_vector(ray->direction, *obj->vector);
	t_vec	cross = cross_vector(subtract_vector(ray->origin, *obj->coord), *obj->vector);
	
	abc[0] = length_squared(d);
	abc[1] = 2.0 * scalar_vector(d, cross);
	abc[2] = length_squared(cross) - pow(obj->radius, 2);
	
	t[0] = (-abc[1] - sqrt(pow(abc[1], 2) - 4.0 * abc[0] * abc[2])) / (2.0 * abc[0]);
	t[1] = (-abc[1] + sqrt(pow(abc[1], 2) - 4.0 * abc[0] * abc[2])) / (2.0 * abc[0]);
	if (t[1] < t[0] && t[1] > T_MIN)
		t[0] = t[1];
	if (t[0] > T_MIN && t[0] < T_MAX && t[0] < ray->closest_t)
	{
		inter = point_at(*ray, t[0]);
		x = sqrt(pow(length_vector(subtract_vector(inter, *obj->coord)) ,2) - pow(obj->radius ,2));
		if (x > (obj->hei_fov / 2.0))
			return (false);
		ray->closest_object = obj;
		ray->closest_t = t[0];
		t_vec	s[2];
		s[0] = subtract_vector(inter, factor_mult_vector(*obj->coord, x));
		s[1] = subtract_vector(inter, factor_mult_vector(*obj->coord, x * -1));
		if (length_vector(s[0]) < length_vector(s[1]))
			ray->normal = unit_vector(s[0]);
		else
			ray->normal = unit_vector(s[1]);
		return (true);
	}
	return (false);
}
