/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:22:10 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/14 16:23:16 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// static void	copy_ray(t_ray *ray, t_ray *myray, t_obj *obj)
// {
// 	if (myray->closest_t > T_MIN && myray->closest_t < T_MAX && myray->closest_t < ray->closest_t)
// 	ray->closest_object = obj;
// 	ray->closest_t = myray->closest_t;
// 	ray->normal = myray->normal;
// }

// bool	hit_cylinder(t_ray *ray, t_obj *obj)
// {
// 	t_ray	myray;
// 	// t_ray	myray2;
// 	t_obj	myobj;
// 	t_vec	vec;

// 	myray.origin = ray->origin;
// 	myray.direction = ray->direction;
// 	vec = add_vector(*obj->coord, factor_mult_vector(*obj->vector, obj->hei_fov / 2));
// 	myobj.coord = &vec;
// 	myobj.vector = obj->vector;
// 	myobj.radius = obj->radius;
// 	if (hit_plane(&myray, &myobj) && hit_sphere(&myray, &myobj))
// 		copy_ray(ray, &myray, obj);
// 	*myobj.coord = add_vector(*obj->coord, factor_mult_vector(*obj->vector, obj->hei_fov / -2));
// 	if (hit_plane(&myray, &myobj) && hit_sphere(&myray, &myobj))
// 		copy_ray(ray, &myray, obj);

//     double a = scalar_vector(ray->direction, ray->direction);
//     t_vec m = subtract_vector(ray->origin, *obj->coord);
//     double b = 2 * scalar_vector(ray->direction, m);
//     double c = scalar_vector(m, m) - obj->radius * obj->radius;
//     double discriminant = b * b - 4 * a * c;
//     if (discriminant < 0) {
//         return false;  // no intersection
//     }
//     double t1 = (-b - sqrt(discriminant)) / (2 * a);
//     double t2 = (-b + sqrt(discriminant)) / (2 * a);
//     double t = t1 < t2 ? t1 : t2;
//     t_vec intersection = add_vector(ray->origin, factor_mult_vector(ray->direction, t));
//     if (intersection.z < obj->coord->z - obj->hei_fov / 2 ||
//         intersection.z > obj->coord->z + obj->hei_fov / 2)
//         return false;  // intersection is outside cylinder height
// 	if (t > T_MIN && t < T_MAX && t < ray->closest_t)
// 	{
//     	ray->closest_object = obj;
//     	ray->closest_t = t;
//     	ray->normal = unit_vector(subtract_vector(intersection, *obj->coord));
//     	return true;
// 	}
// 	return (false);

// }


//mit hannes
bool	hit_cylinder(t_ray *ray, t_obj *obj)
{
	double	abc[3];
	double	t[2];
	double	x;
	t_vec	inter;
	t_ray	r_cyl;
	
	r_cyl = new_ray();
	r_cyl.direction = obj->vector;
	r_cyl.origin = *obj->coord;

	t_vec	a;
	a = point_at(r_cyl, length_vector(r_cyl.direction) / 2);

	
	
	ray->direction = unit_vector(ray->direction);
	abc[0] = length_squared(cross_vector(ray->direction, *obj->vector));
	abc[1] = 2.0 * scalar_vector(cross_vector(ray->direction, *obj->vector), cross_vector(subtract_vector(ray->origin, *obj->coord), *obj->vector));
	abc[2] = length_squared(cross_vector(subtract_vector(ray->origin, *obj->coord), *obj->vector)) - pow(obj->radius, 2);
	t[0] = -abc[1] - sqrt(pow(abc[1], 2) - 4.0 * abc[0] * abc[2]) / (2.0 * abc[0]);
	t[1] = -abc[1] + sqrt(pow(abc[1], 2) - 4.0 * abc[0] * abc[2]) / (2.0 * abc[0]);
	if (t[1] < t[0] && t[1] > T_MIN)
		t[0] = t[1];
	if (t[0] > T_MIN && t[0] < T_MAX && t[0] < ray->closest_t)
	{
		// inter = point_at(*ray, t[0]);
		inter = add_vector(ray->origin, factor_mult_vector(ray->direction, t[0]));
		x = sqrt(pow(length_vector(subtract_vector(inter, *obj->coord)) ,2) - pow(obj->radius ,2));
		// if (x < 30.0)
			// printf("A_x = %f, height:%f\n", x, obj->hei_fov / 2.0);
		if (x < (obj->hei_fov / 2.0))
			return (false);
		// print_vector(ray->direction);
		print_vector(inter);
		printf("\n");
		ray->closest_object = obj;
		ray->closest_t = t[0];
		if (scalar_vector(*obj->vector, ray->direction) > 0)
			ray->normal = subtract_vector(inter, factor_mult_vector(*obj->vector, t[0] * -1.0));
		else
			ray->normal = subtract_vector(inter, factor_mult_vector(*obj->vector, t[0]));
		return (true);
	}
	return (false);
}
