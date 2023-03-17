/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:22:10 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/17 17:07:44 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_cylinder(t_ray *ray, t_obj *obj)
{
	double	abc[3];
	double	t[2];
	double	x;
	double	val;
	t_vec	inter;

	val = NAN;
	ray->direction = unit_vector(ray->direction);
	t_vec	d = cross_vector(ray->direction, obj->vector);
	t_vec	cross = cross_vector(subtract_vector(ray->origin, obj->coord), obj->vector);
	abc[0] = length_squared(d);
	abc[1] = 2.0 * scalar_vector(d, cross);
	abc[2] = length_squared(cross) - pow(obj->radius, 2);
	if (abc[0] != 0)
	{
		t[0] = (-abc[1] - sqrt(pow(abc[1], 2) - (4.0 * abc[0] * abc[2]))) / (2.0 * abc[0]);
		t[1] = (-abc[1] + sqrt(pow(abc[1], 2) - (4.0 * abc[0] * abc[2]))) / (2.0 * abc[0]);
	}
	if (isnan(t[0]) && isnan(t[1]))
		return (false);
	else if (isnan(t[0]) && !isnan(t[1]))
		val = t[1];
	else if (!isnan(t[0]) && isnan(t[1]))
		val = t[0];
	else if (!isnan(t[0]) && !isnan(t[1]))
		val = fmin(t[0], t[1]);
	if (val > T_MIN && val < T_MAX && val < ray->closest_t)
	{
		inter = point_at(*ray, val );
		x = sqrt(length_squared(subtract_vector(inter, obj->coord)) - pow(obj->radius ,2));
		if (x > obj->hei_fov / 2.0 )
			return (false);
		ray->closest_object = obj;
		ray->closest_t = val;
		t_vec	s[2];
		s[0] = subtract_vector(subtract_vector(inter, obj->coord), factor_mult_vector(obj->vector, x));
		s[1] = subtract_vector(subtract_vector(inter, obj->coord), factor_mult_vector(obj->vector, -x));
		if (length_vector(s[0]) < length_vector(s[1]))
			ray->normal = unit_vector(s[0]);
		else
			ray->normal = unit_vector(s[1]);
		return (true);
	}
	return (false);
}
