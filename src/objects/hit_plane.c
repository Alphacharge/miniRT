/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:42:09 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/16 18:44:25 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_plane(t_ray *ray, t_obj *obj)
{
	double	ortho;
	double	pln_d;
	double	dis;
	double	t;

	ortho = scalar_vector(*obj->vector, ray->direction);
	if (ortho == 0)
		return (false);
	pln_d = scalar_vector(*obj->coord, *obj->vector);
	dis = scalar_vector(*obj->vector, ray->origin);
	t = (pln_d - dis) / ortho;
	if (t < T_MIN || t > T_MAX)
		return (false);
	if (t < ray->closest_t)
	{
		ray->closest_object = obj;
		ray->closest_t = t;
		ray->normal = *obj->vector;
		return (true);
	}
	return (false);
}
