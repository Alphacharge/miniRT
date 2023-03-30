/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:22:10 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/30 13:15:31 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	midnight(t_ray *ray, t_obj *obj)
{
	double	a[3];
	double	t[2];
	double	val;
	t_vec	d;
	t_vec	cros;

	val = NAN;
	ray->direction = unit_vector(ray->direction);
	d = cross_vector(ray->direction, obj->vector);
	cros = cross_vector(subtract_vector(ray->origin, obj->origin), obj->vector);
	a[0] = length_squared(d);
	a[1] = 2.0 * scalar_vector(d, cros);
	a[2] = length_squared(cros) - pow(obj->radius, 2);
	if (a[0] == 0)
		return (0);
	t[0] = (-a[1] - sqrt(pow(a[1], 2) - (4.0 * a[0] * a[2]))) / (2.0 * a[0]);
	t[1] = (-a[1] + sqrt(pow(a[1], 2) - (4.0 * a[0] * a[2]))) / (2.0 * a[0]);
	if (t[0] < T_MIN || t[0] > T_MAX || isnan(t[0]))
		t[0] = T_MAX;
	if (t[1] < T_MIN || t[1] > T_MAX || isnan(t[1]))
		t[1] = T_MAX;
	val = t[0];
	if (t[1] < t[0])
		val = t[1];
	return (val);
}

// t_vec	decide_normal(t_vec inter, t_vec origin, t_vec vector, double x)
// {

// }
bool	hit_cylinder(t_ray *ray, t_obj *obj)
{
	double	x;
	double	val;
	t_vec	inter;
	t_vec	s[2];

	val = midnight(ray, obj);
	if (val >= T_MAX || val == 0)
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
