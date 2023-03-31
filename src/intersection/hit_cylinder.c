/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:22:10 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/31 11:08:55 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	smallest_t(double t1, double t2)
{
	double	val;

	val = NAN;
	if (t1 < T_MIN || t1 > T_MAX || isnan(t1))
		t1 = T_MAX;
	if (t2 < T_MIN || t2 > T_MAX || isnan(t2))
		t2 = T_MAX;
	val = t1;
	if (t2 < t1)
		val = t2;
	return (val);
}

double	midnight(t_ray *ray, t_obj *obj)
{
	double	a[3];
	double	t[2];
	t_vec	d;
	t_vec	cros;

	d = new_vector(0, 0, 0);
	cros = new_vector(0, 0, 0);
	d = cross_vector(ray->direction, obj->vector);
	cros = cross_vector(subtract_vector(ray->origin, obj->origin), obj->vector);
	a[0] = length_squared(d);
	a[1] = 2.0 * scalar_vector(d, cros);
	a[2] = length_squared(cros) - (obj->radius * obj->radius);
	if (a[0] == 0)
		return (0);
	t[0] = (-a[1] - sqrt((a[1] * a[1]) - (4.0 * a[0] * a[2]))) / (2.0 * a[0]);
	t[1] = (-a[1] + sqrt((a[1] * a[1]) - (4.0 * a[0] * a[2]))) / (2.0 * a[0]);
	return (smallest_t(t[0], t[1]));
}

t_vec	decide_normal(t_vec inter, t_vec origin, t_vec vector, double x)
{
	t_vec	s[2];
	t_vec	res;

	s[0] = new_vector(0, 0, 0);
	s[1] = new_vector(0, 0, 0);
	res = new_vector(0, 0, 0);
	s[0] = subtract_vector(subtract_vector(inter, origin), \
			factor_mult_vector(vector, x));
	s[1] = subtract_vector(subtract_vector(inter, origin), \
			factor_mult_vector(vector, -x));
	if (length_vector(s[0]) < length_vector(s[1]))
		res = unit_vector(s[0]);
	else
		res = unit_vector(s[1]);
	return (res);
}

bool	hit_cylinder(t_ray *ray, t_obj *obj)
{
	double	x;
	double	val;
	t_vec	inter;

	inter = new_vector(0, 0, 0);
	val = midnight(ray, obj);
	if (val >= T_MAX || val == 0)
		return (false);
	if (val > T_MIN && val < T_MAX && val < ray->closest_t)
	{
		inter = point_at(*ray, val);
		x = sqrt(length_squared(subtract_vector(inter, obj->origin)) \
			- pow(obj->radius, 2.0));
		if (x > obj->hei_fov / 2.0)
			return (false);
		ray->closest_object = obj;
		ray->closest_t = val;
		ray->normal = decide_normal(inter, obj->origin, obj->vector, x);
		return (true);
	}
	return (false);
}
