/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:42:25 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/04 14:14:37 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// t_ray	*new_ray(t_vec *origin, t_vec *direction)
// {
// 	t_ray	*ray;

// 	ray = ft_calloc(1, sizeof(t_ray));
// 	if (ray == NULL)
// 		return (NULL);
// 	ray->origin = origin;
// 	ray->direction = direction;
// 	return (ray);
// }

// t_ray	*delete_ray(t_ray *ray)
// {
// 	if (ray == NULL)
// 		return (NULL);
// 	ft_free(ray->direction);
// 	ft_free(ray->origin);
// 	ft_free(ray);
// 	return (NULL);
// }

t_vec	point_at(t_ray *ray, double t)
{
	t_vec	product;
	t_vec	point;

	product = factor_mult_vector(ray->direction, t);
	point = add_vector(ray->origin, product);
	return (point);
}

bool	front_facing(t_ray *ray)
{
	if (scalar_vector(ray->direction, ray->normal) >= 0)
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
		ray->normal = point_at(ray, t);
		ray->normal = subtract_vector(ray->normal, *obj->coord);
		ray->normal = factor_div_vector(ray->normal, obj->rad_rat);
	}
	return (true);
}

bool	hit_object(t_ray *ray, t_obj *obj)
{
	while (obj != NULL)
	{
		if (obj->type == SPHERE && hit_sphere(ray, obj) == true)
		{
printf("true ");
			return (true);
		}
		obj = obj->next;
	}
	return (false);
}

int	ray_color(t_ray *ray, t_obj *obj)
{
	double			t;

	if (hit_object(ray, obj) == true)
	{
		// if (front_facing(ray) == true)
			// return (double_to_color(fabs(ray->normal.x), fabs(ray->normal.y), fabs(ray->normal.z)));
			return (double_to_color(0.1, 0.1, fabs(ray->normal.z)));
		// else
		// 	return (0xBB3333FF);
	}
	t = 0.5 * (unit_vector(ray->direction).y + 1.0);
	return (add_color \
		(factor_color(0x5588FFFF, 1 - t), factor_color(0xFFFFFFFF, t)));
}
