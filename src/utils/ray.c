/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:42:25 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/07 18:06:34 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	new_ray()
{
	t_ray	ray;

	ray.closest_object = NULL;
	ray.closest_t = T_MAX;
	ray.direction.x = 0;
	ray.direction.y = 0;
	ray.direction.z = 0;
	ray.origin.x = 0;
	ray.origin.y = 0;
	ray.origin.z = 0;
	ray.normal.x = 0;
	ray.normal.y = 0;
	ray.normal.z = 0;
	return (ray);
}

t_vec	point_at(t_ray ray, double t)
{
	t_vec	product;
	t_vec	target;

	product = factor_mult_vector(ray.direction, t);
	target = add_vector(ray.origin, product);
	return (target);
}

bool	front_facing(t_ray ray)
{
	if (scalar_vector(ray.direction, ray.normal) >= 0)
		return (false);
	return (true);
}

bool	hit_sphere(t_ray *ray, t_obj *obj)
{
	t_vec	origin_center;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;
	double	length;

	origin_center = subtract_vector(ray->origin, *obj->coord);
	length = length_vector(ray->direction);
	a = pow(length, 2);
	b = scalar_vector(origin_center, ray->direction);
	length = length_vector(origin_center);
	c = pow(length, 2) - pow(obj->rad_rat, 2);
	discriminant = b * b - a * c;
	if (discriminant < 0)
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
		ray->normal = subtract_vector(ray->normal, *obj->coord);
		ray->normal = factor_div_vector(ray->normal, obj->rad_rat);
	}
	return (true);
}

bool	hit_object(t_ray *ray, t_obj *obj)
{
	bool	hit_anything;

	hit_anything = false;
	while (obj != NULL)
	{
		if (obj->type == SPHERE && hit_sphere(ray, obj) == true)
			hit_anything = true;
		obj = obj->next;
	}
	return (hit_anything);
}

/*Sphere sampling:
		bounce.origin = point_at(ray, ray.closest_t);
		target = add_vector(bounce.origin, ray.normal);
		seed = xslcg_random(seed);
		target = add_vector(target, unit_vector(rand_in_unit_sphere(seed)));
		bounce.direction = subtract_vector(target, bounce.origin);
		return (factor_color(ray_color(bounce, obj, depth - 1), 0.5));
Hemisphere sampling:
		bounce.origin = point_at(ray, ray.closest_t);
		target = add_vector(bounce.origin, rand_in_hemisphere(seed, ray.normal));
		seed = xslcg_random(seed);
		bounce.direction = subtract_vector(target, bounce.origin);
		return (factor_color(ray_color(bounce, obj, depth - 1), 0.5));
*/
int	ray_color(t_ray ray, t_obj *obj, int depth)
{
	t_vec	target;
	double	t;
	t_ray	bounce;
	static int	seed = (int)883082594;

	bounce = new_ray();
	if (depth <= 0)
		return (0xFF0000FF);
	if (hit_object(&ray, obj) == true)
	{
		bounce.origin = point_at(ray, ray.closest_t);
		target = add_vector(bounce.origin, ray.normal);
		seed = xslcg_random(seed);
		target = add_vector(target, unit_vector(rand_in_unit_sphere(seed)));
		bounce.direction = subtract_vector(target, bounce.origin);
		if (front_facing(ray) == true)
			// return (double_to_color(fabs(ray.normal.x), fabs(ray.normal.y), fabs(ray.normal.z)));
			// return (0.5 * ray_color(bounce, obj));
			return (factor_color(ray_color(bounce, obj, depth - 1), 0.5));
		else
			return (0xBB3333FF);
	}
	t = 0.5 * (unit_vector(ray.direction).y + 1.0);
	return (add_color \
		(factor_color(0x5588FFFF, 1 - t), factor_color(0xFFFFFFFF, t)));
}
