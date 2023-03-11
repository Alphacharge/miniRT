/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:22:10 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/11 14:49:06 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//this version shows only the circle part of the cylinder and only 1 of it

bool	hit_cylinder(t_ray *ray, t_obj *obj)
{
	double	t;
	double	dist;
	double	div;
	t_vec	inter;
	t_vec	proj;
	// Step 3: Calculate t
	div = scalar_vector(ray->direction, *obj->vector);
	if (div == 0)
		return (false);
	t = (scalar_vector(*obj->coord, *obj->vector) - scalar_vector(ray->origin, *obj->vector)) / div;
	if (t < T_MIN || t > T_MAX)
		return (false);
	// Step 4: Calculate the coordinates of the intersection point
	inter = add_vector(ray->origin, factor_mult_vector(ray->direction, t));
	// Step 5: Check if the intersection point lies on the lateral surface of the cylinder
	proj = add_vector(*obj->coord, factor_mult_vector(*obj->vector, scalar_vector(subtract_vector(inter, *obj->coord), *obj->vector)));
	dist = sqrt(pow(inter.x - proj.x, 2) + pow(inter.y - proj.y, 2) + pow(inter.z - proj.z, 2));
	if (dist <= obj->radius && proj.x >= obj->coord->x - obj->hei_fov / 2 && proj.x <= obj->coord->x + obj->hei_fov / 2)
	{
		ray->closest_object = obj;
		ray->closest_t = t;
		ray->normal = *obj->vector;
		return (true);
	}
	else
		return (false); // No intersection or intersection not on the lateral surface of the cylinder
}


//this function renders me a curve
// bool hit_cylinder(t_ray *ray, t_obj *obj)
// {
// 	t_vec	m;
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	discr;
// 	double	t1;
// 	double	t2;
// 	double	t;
// 	t_vec	intersection;
// 	m = subtract_vector(ray->origin, *obj->coord);
// 	a = scalar_vector(ray->direction, ray->direction) - pow(scalar_vector(ray->direction, *obj->vector), 2);
// 	b = 2 * (scalar_vector(ray->direction, m) - scalar_vector(ray->direction, *obj->vector) * scalar_vector(m, *obj->vector));
// 	c = scalar_vector(m, m) - pow(scalar_vector(m, *obj->vector), 2) - pow(obj->radius, 2);
// 	discr = b * b - 4 * a * c;
// 	if (discr < 0 || a == 0)
// 		return (false); // no intersection
// 	t1 = (-b + sqrt(discr)) / (2 * a);
// 	t2 = (-b - sqrt(discr)) / (2 * a);
// 	if (t1 < t2)
// 		t = t1;
// 	else
// 		t = t2;
// 	intersection = add_vector(ray->origin, factor_mult_vector(ray->direction, t));
// 	if (intersection.z < obj->coord->z || intersection.z > obj->coord->z + obj->hei_fov)
// 	    return (false); // intersection is outside cylinder height
// 	ray->closest_object = obj;
// 	ray->closest_t = t;
// 	ray->normal = *obj->vector;
// 	return (true);
// }
