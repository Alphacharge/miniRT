/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:50:50 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/31 13:55:39 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	is_closest(t_ray *ray, t_obj *obj, double t)
{
	if (t >= ray->closest_t)
		return (false);
	ray->closest_t = t;
	ray->closest_object = obj;
	ray->normal = unit_vector(obj->vector);
	return (true);
}

double	x_in_plane(t_vec obj_n, t_vec obj_o, t_vec ray_n, t_vec ray_o)
{
	double	ortho;
	double	pln_d;
	double	dis;
	double	t;

	ortho = scalar_vector(obj_n, ray_n);
	if (ortho == 0)
		return (0);
	pln_d = scalar_vector(obj_o, obj_n);
	dis = scalar_vector(obj_n, ray_o);
	t = (pln_d - dis) / ortho;
	return (t);
}

bool	hit_square(t_ray *ray, t_obj *obj)
{
	double	txy[3];
	t_vec	diff;
	t_vec	inter;

	diff = new_vector(0, 0, 0);
	inter = new_vector(0, 0, 0);
	txy[0] = t_to_plane(obj->vector, obj->origin, ray->direction, ray->origin);
	if (txy[0] == 0)
		return (false);
	inter = point_at(*ray, txy[0]);
	diff = subtract_vector(inter, obj->origin);
	txy[1] = x_in_plane(obj->vector2, inter, obj->vector2, obj->origin);
	txy[2] = sqrt(length_squared(diff) - txy[1] * txy[1]);
	if (txy[1] < 0)
		txy[1] = txy[1] * -1;
	if (txy[2] < 0)
		txy[2] = txy[2] * -1;
	if (txy[1] > obj->radius / 2 || txy[2] > obj->width / 2)
		return (false);
	return (is_closest(ray, obj, txy[0]));
}
