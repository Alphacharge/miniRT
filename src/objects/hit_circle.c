/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:50:50 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/15 12:40:41 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_circle(t_ray *ray, t_obj *obj)
{
	double	ortho;
	double	pln_d;
	double	dis;
	double	t;
	double	r;

	ortho = scalar_vector(*obj->vector, ray->direction);
	if (ortho == 0)
		return (false);
	pln_d = scalar_vector(*obj->coord, *obj->vector);
	dis = scalar_vector(*obj->vector, ray->origin);
	t = (pln_d - dis) / ortho;
	r = length_vector(subtract_vector(*obj->coord, add_vector(ray->origin, factor_mult_vector(unit_vector(ray->direction), t))));
	if (r > obj->radius || t < T_MIN || t > T_MAX)
		return (false);
	if (t < ray->closest_t)
	{
		ray->closest_object = obj;
		ray->closest_t = t;
		ray->normal = unit_vector(*obj->vector);
	}
	return (true);
}
