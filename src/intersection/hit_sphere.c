/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:41:17 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/31 11:15:07 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	closest_intersection(double root, double a, double b)
{
	double	t;

	t = (-b - root) / a;
	if (t < T_MIN || T_MAX < t)
	{
		t = (-b + root) / a;
		if (t < T_MIN || T_MAX < t)
			return (T_MAX);
	}
	return (t);
}

static bool	closest_sphere(t_ray *ray, t_obj *obj, double t)
{
	if (t >= ray->closest_t)
		return (false);
	ray->closest_t = t;
	ray->closest_object = obj;
	ray->normal = point_at(*ray, t);
	ray->normal = subtract_vectors(ray->normal, obj->origin);
	ray->normal = divide_vector_by_scalar(ray->normal, obj->radius);
	return (true);
}

bool	hit_sphere(t_ray *ray, t_obj *obj)
{
	t_vec	origin_center;
	double	a;
	double	b;
	double	discriminant;
	double	length;

	origin_center = new_vector(0, 0, 0);
	origin_center = subtract_vectors(ray->origin, obj->origin);
	length = length_vector(ray->direction);
	a = length * length;
	b = dot_product(origin_center, ray->direction);
	length = length_vector(origin_center);
	discriminant = b * b - ((a * length * length) - \
		(obj->radius * obj->radius));
	if (discriminant <= 0)
		return (false);
	discriminant = sqrt(discriminant);
	return (closest_sphere(ray, obj, closest_intersection(discriminant, a, b)));
}
