/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:22:10 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/10 18:23:24 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_cylinder(t_ray *ray, t_obj *obj)
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
	}
	return (true);
}
#include <math.h>

 {
    
    // Step 3: Calculate t
	
    double numerator = scalar_vector(subtract_vector(obj->coord, ray->origin), *obj->vector);
    double denominator = scalar_vector(*ray->direction, *obj->vector);
    double t = numerator / denominator;
    
    // Step 4: Calculate the coordinates of the intersection point
    double intersection_x = ray->origin->x + t * ray->direction->x;
    double intersection_y = ray->origin->y + t * ray->direction->y;
    double intersection_z = ray->origin->z + t * ray->direction->z;
    
    // Step 5: Check if the intersection point lies on the lateral surface of the cylinder
	t_vec inter;
	t_vec proj;
    double dot_product = scalar_vector(subtract_vector(inter, obj->coord), obj->vector);
	double proj = scalar_vector()
    double proj.x = obj->coord->x + dot_product * obj->vector->x;
    double proj.y = obj->coord->y + dot_product * obj->vector->y;
    double proj.z = obj->coord->z + dot_product * obj->vector->z;
    double dist = sqrt(pow(intersection_x - proj.x, 2)
                       + pow(intersection_y - proj.y, 2)
                       + pow(intersection_z - proj.z, 2));
    if (dist <= obj->radius && proj.x >= obj->coord->x - obj->height / 2
        && proj.x <= obj->coord->x + obj->height / 2) {
			ray->closest_object = obj;
		ray->closest_t = t;
		ray->normal = *obj->vector;
        return true;
    } else {
        return false; // No intersection or intersection not on the lateral surface of the cylinder
    }
}
