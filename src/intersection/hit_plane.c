/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:42:09 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/28 13:16:36 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	t_to_plane(t_vec obj_n, t_vec obj_o, t_vec ray_n, t_vec ray_o)
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
	if (t < T_MIN || t > T_MAX)
		return (0);
	return (t);
}

bool	hit_plane(t_ray *ray, t_obj *obj)
{
	double	t;

	t = t_to_plane(obj->vector, obj->origin, ray->direction, ray->origin);
	if (t == 0)
		return (false);
	if (t < ray->closest_t)
	{
		ray->closest_object = obj;
		ray->closest_t = t;
		ray->normal = obj->vector;
		return (true);
	}
	return (false);
}
