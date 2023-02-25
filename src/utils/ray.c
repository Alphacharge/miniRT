/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:42:25 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/25 19:55:25 by fkernbac         ###   ########.fr       */
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

t_vec	*point_at(t_ray *ray, float t)
{
	t_vec	*product;
	t_vec	*point;

	product = factor_mult_vector(ray->direction, t);
	point = add_vector(ray->origin, product);
	ft_free(product);
	return (point);
}

int	ray_color(t_ray *ray)
{
	t_vec	*unit_direction;
	float	t;

	unit_direction = unit_vector(ray->direction);
	t = 0.5 * (unit_direction->y + 1.0);
	ft_free(unit_direction);
printf("t %f\n", t);
	// return (add_color(multiply_color(0xFFFFFFFF, 1.0 - t), multiply_color(0x88BBFFFF, t)));
	return (add_color(0xFF0000FF, 0x00FF00FF));
}
