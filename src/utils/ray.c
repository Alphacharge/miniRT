/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:42:25 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/27 21:01:09 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	*new_ray(t_vec *origin, t_vec *direction)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	if (ray == NULL)
		return (NULL);
	ray->origin = origin;
	ray->direction = direction;
	return (ray);
}

t_ray	*delete_ray(t_ray *ray)
{
	if (ray == NULL)
		return (NULL);
	ft_free(ray->direction);
	ft_free(ray->origin);
	ft_free(ray);
	return (NULL);
}

t_vec	*point_at(t_ray *ray, float t)
{
	t_vec	*product;
	t_vec	*point;

	product = factor_mult_vector(ray->direction, t);
	point = add_vector(ray->origin, product);
	ft_free(product);
	return (point);
}

int	ray_hit_sphere(t_ray *ray, t_vec *center, float radius)
{
	t_vec	*origin_center;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	origin_center = subtract_vector(ray->origin, center);
	a = pow(length_vector(ray->direction), 2);
	b = scalar_vector(origin_center, ray->direction);
	c = pow(length_vector(origin_center), 2) - pow(radius, 2);
	discriminant = b * b - a * c;
	ft_free(origin_center);
	if (discriminant < 0)
		return (0);
	return (1);
}

int	ray_color(t_ray *ray)
{
	t_vec		*unit;
	t_vec		*table[10];
	float		t;
	unsigned int	color1;
	unsigned int	color2;
	t_vec		*center;

	center = new_vector(-50, 100, 500);
	t = ray_hit_sphere(ray, center, 200);
	if (t > 0.0)
	{
		table[0] = point_at(ray, t);
		table[1] = new_vector(0, 0, -1);
		table[2] = subtract_vector(table[0],table[1]);
		unit = unit_vector(table[2]);
		color1 = float_to_color((unit->x + 1) * 0.5, (unit->y + 1) * 0.5, (unit->z + 1) * 0.5);
		ft_free(table[0]);
		ft_free(table[1]);
		ft_free(table[2]);
		ft_free(unit);
		return (color1);
	}
	unit = unit_vector(ray->direction);
	t = 0.5 * (unit->y + 1.0);
	ft_free(unit);
	color1 = factor_color(0x5588FFFF, 1 - t);
	color2 = factor_color(0xFFFFFFFF, t);
	return (add_color(color1, color2));
}

int	front_face(t_ray *ray, t_vec *normal)
{
	//ray inside sphere
	if (scalar_vector(ray->direction, normal) > 0.0)
		return (0);
	//ray outside sphere
	return (1);
}
