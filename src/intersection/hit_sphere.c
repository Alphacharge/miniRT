/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:41:17 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/27 14:14:03 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_sphere(t_ray *ray, t_obj *obj)
{
	t_vec	origin_center;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;
	double	length;

	t = T_MAX;
	discriminant = 0;
	origin_center = subtract_vector(ray->origin, obj->origin);
	length = length_vector(ray->direction);
	a = pow(length, 2);
	b = scalar_vector(origin_center, ray->direction);
	length = length_vector(origin_center);
	c = pow(length, 2) - pow(obj->radius, 2);
	discriminant = b * b - a * c;
	if (discriminant <= 0)
		return (false);
	discriminant = sqrt(discriminant);
	t = (-b - discriminant) / a;
	if (t < T_MIN || T_MAX < t)
	{
		t = (-b + discriminant) / a;
		if (t < T_MIN || T_MAX < t)
			return (false);
	}
	if (t < ray->closest_t)
	{
		ray->closest_t = t;
		ray->closest_object = obj;
		ray->normal = point_at(*ray, t);
		ray->normal = subtract_vector(ray->normal, obj->origin);
		ray->normal = factor_div_vector(ray->normal, obj->radius);
		return (true);
	}
	return (false);
}
