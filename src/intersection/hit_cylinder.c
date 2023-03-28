/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:22:10 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/28 11:25:25 by rbetz            ###   ########.fr       */
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
	t_vec	s[2];
	t_vec	d;
	t_vec	cross;

	val = NAN;
	ray->direction = unit_vector(ray->direction);
	d = cross_vector(ray->direction, obj->vector);
	cross = cross_vector(subtract_vector(ray->origin, obj->origin), obj->vector);
	abc[0] = length_squared(d);
	abc[1] = 2.0 * scalar_vector(d, cross);
	abc[2] = length_squared(cross) - pow(obj->radius, 2);
	if (abc[0] == 0)
		return (false);
	t[0] = (-abc[1] - sqrt(pow(abc[1], 2) - (4.0 * abc[0] * abc[2]))) / (2.0 * abc[0]);
	t[1] = (-abc[1] + sqrt(pow(abc[1], 2) - (4.0 * abc[0] * abc[2]))) / (2.0 * abc[0]);
	if (t[0] < T_MIN || t[0] > T_MAX || isnan(t[0]))
		t[0] = T_MAX;
	if (t[1] < T_MIN || t[1] > T_MAX || isnan(t[1]))
		t[1] = T_MAX;
	val = t[0];
	if (t[1] < t[0])
		val = t[1];
	if (val >= T_MAX)
		return (false);
	if (val > T_MIN && val < T_MAX && val < ray->closest_t)
	{
		inter = point_at(*ray, val);
		x = sqrt(length_squared(subtract_vector(inter, obj->origin)) - pow(obj->radius, 2));
		if (x > obj->hei_fov / 2.0)
			return (false);
		ray->closest_object = obj;
		ray->closest_t = val;
		s[0] = subtract_vector(subtract_vector(inter, obj->origin), factor_mult_vector(obj->vector, x));
		s[1] = subtract_vector(subtract_vector(inter, obj->origin), factor_mult_vector(obj->vector, -x));
		if (length_vector(s[0]) < length_vector(s[1]))
			ray->normal = unit_vector(s[0]);
		else
			ray->normal = unit_vector(s[1]);
		return (true);
	}
	return (false);
}
