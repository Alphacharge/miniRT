/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:42:25 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/03 17:26:11 by fkernbac         ###   ########.fr       */
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

//this might be only a temporary struct
t_sphere	*new_sphere(double x, double y, double z, double radius)
{
	t_sphere	*sphere;

	sphere = ft_calloc(1, sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->center = ft_calloc(1, sizeof(t_vec));
	if (sphere->center == NULL)
		return (NULL);
	sphere->center->x = x;
	sphere->center->y = y;
	sphere->center->z = z;
	sphere->radius = radius;
	return (sphere);
}

bool	hit_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vec	origin_center;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;
	double	length;

	origin_center = subtract_vector(ray->origin, *sphere->center);
	length = length_vector(ray->direction);
	a = pow(length, 2);
	b = scalar_vector(origin_center, ray->direction);
	length = length_vector(origin_center);
	c = pow(length, 2) - pow(sphere->radius, 2);
	discriminant = b * b - a * c;
	if (discriminant < 0)
		return (false);
	discriminant = sqrt(discriminant);
	t = (-b - discriminant) / a;
	if (t < T_MIN || T_MAX < t)
	{
printf("t %f ", t);
		t = (-b + discriminant) / a;
		if (t < T_MIN || T_MAX < t)
			return (false);
	}
	if (t < ray->closest_t)
	{
		ray->closest_t = t;
		ray->closest_object = sphere;
		ray->normal = point_at(ray, t);
		ray->normal = subtract_vector(ray->normal, *sphere->center);
		ray->normal = factor_div_vector(ray->normal, sphere->radius);
	}
	return (true);
}

bool	hit_object(t_ray *ray, t_sphere *sphere)
{
	bool	hit_anything;

	hit_anything = false;
	if (hit_sphere(ray, sphere) == true)
		hit_anything = true;
	return (hit_anything);
}

int	ray_color(t_ray *ray)
{
	t_vec			unit;
	unsigned int	color1;
	unsigned int	color2;
	double			t;

	t_sphere	*sphere1;
	t_sphere	*sphere2;
	sphere1 = new_sphere(150, 50, -300, 100);
	sphere2 = new_sphere(0, 0, -150, 100);

	if (hit_object(ray, sphere1) == true || hit_object(ray, sphere2) == true)
	{
		if (front_facing(ray) == true)
			// return (double_to_color(fabs(ray->normal.x), fabs(ray->normal.y), fabs(ray->normal.z)));
			return (double_to_color(0.1, 0.1, fabs(ray->normal.z)));
		else
			return (0xBB3333FF);
	}
	unit = unit_vector(ray->direction);
	t = 0.5 * (unit.y + 1.0);
	color1 = factor_color(0x5588FFFF, 1 - t);
	color2 = factor_color(0xFFFFFFFF, t);
	return (add_color(color1, color2));
}
