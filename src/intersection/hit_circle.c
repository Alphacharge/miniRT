/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:50:50 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/28 12:59:32 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_circle(t_ray *ray, t_obj *obj)
{
	double	t;
	double	r;

	t = t_to_plane(obj->vector, obj->origin, ray->direction, ray->origin);
	if (t == 0)
		return (false);
	r = length_vector(subtract_vector(obj->origin, point_at(*ray, t)));
	if (r < 0)
		r *= -1;
	if (r > obj->radius)
		return (false);
	if (t < ray->closest_t)
	{
		ray->closest_object = obj;
		ray->closest_t = t;
		ray->normal = unit_vector(obj->vector);
		return (true);
	}
	return (false);
}
