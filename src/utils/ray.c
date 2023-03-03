/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:42:25 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/03 14:11:05 by fkernbac         ###   ########.fr       */
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

t_vec	point_at(t_ray *ray, float t)
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

int	ray_color(t_ray *ray)
{
	t_vec			unit;
	unsigned int	color1;
	unsigned int	color2;
	float			t;

	// unit = unit_vector(ray->direction);
	unit = ray->normal;
	if (ray->closest_object != NULL)
	{
		printf("unit.x: %f ", unit.x);
		if (front_facing(ray) == true)
			return (float_to_color(unit.x, 0, 0));
		// else
		// 	return (0x000000FF);
	}
	t = 0.5 * (unit.y + 1.0);
	color1 = factor_color(0x5588FFFF, 1 - t);
	color2 = factor_color(0xFFFFFFFF, t);
	return (add_color(color1, color2));
}
