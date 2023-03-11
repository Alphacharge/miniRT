/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:22:10 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/11 12:21:22 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// bool	hit_cylinder(t_ray *ray, t_obj *obj)
// {
// 	double	t;
// 	double	dist;
// 	double	div;
// 	t_vec	inter;
// 	t_vec	proj;
// 	// Step 3: Calculate t
// 	div = scalar_vector(ray->direction, *obj->vector);
// 	if (div == 0)
// 		return (false);
// 	t = (scalar_vector(*obj->coord, *obj->vector) - scalar_vector(ray->origin, *obj->vector)) / div;
// 	if (t < T_MIN || t > T_MAX)
// 		return (false);
// 	// Step 4: Calculate the coordinates of the intersection point
// 	inter = add_vector(ray->origin, factor_mult_vector(ray->direction, t));
// 	// Step 5: Check if the intersection point lies on the lateral surface of the cylinder
// 	proj = add_vector(*obj->coord, factor_mult_vector(*obj->vector, scalar_vector(subtract_vector(inter, *obj->coord), *obj->vector)));
// 	dist = sqrt(pow(inter.x - proj.x, 2) + pow(inter.y - proj.y, 2) + pow(inter.z - proj.z, 2));
// 	if (dist <= obj->radius && proj.x >= obj->coord->x - obj->hei_fov / 2 && proj.x <= obj->coord->x + obj->hei_fov / 2)
// 	{
// 		printf("hit,");
// 		ray->closest_object = obj;
// 		ray->closest_t = t;
// 		ray->normal = *obj->vector;
// 		return (true);
// 	}
// 	else
// 		return (false); // No intersection or intersection not on the lateral surface of the cylinder
// }

bool hit_cylinder(t_ray *ray, t_obj *obj)
{
	// printf("1,");
	t_vec m = subtract_vector(ray->origin, *obj->coord);
	// printf("2,");
	double a = scalar_vector(ray->direction, ray->direction) - pow(scalar_vector(ray->direction, *obj->vector), 2);
	// printf("a:%f", a);
	// printf("3,");
	double b = 2 * (scalar_vector(ray->direction, m) - scalar_vector(ray->direction, *obj->vector) * scalar_vector(m, *obj->vector));
	// printf("4,");
	double c = scalar_vector(m, m) - pow(scalar_vector(m, *obj->vector), 2) - pow(obj->radius, 2);
	// printf("5,");
	double discr = b * b - 4 * a * c;
	// printf("6,");
	if (discr < 0 || a == 0)
		return (false); // no intersection
	// printf("7,");
	// printf("t1:%f", a);
	double t1 = (-b + sqrt(discr)) / (2 * a);
	// printf("8,");
	double t2 = (-b - sqrt(discr)) / (2 * a);
	// printf("9,");
	double t;
	if (t1 < t2)
		t = t1;
	else
		t = t2;
	// printf("10,");
	// print_vector(ray->origin);
	// print_vector(ray->direction);
	// printf("t:%f", t);
	t_vec intersection = add_vector(ray->origin, factor_mult_vector(ray->direction, t));
	// printf("11,");
	if (intersection.z < obj->coord->z || intersection.z > obj->coord->z + obj->hei_fov) {
	    return (false); // intersection is outside cylinder height
	}
	return (true);
}


// bool hit_cylinder(t_ray *ray, t_obj *obj) {
    
//     // Step 3: Calculate t
// 	printf("1,");
//     double numerator = (obj->coord->x - ray->origin.x) * obj->vector->x
//                         + (obj->coord->y - ray->origin.y) * obj->vector->y
//                         + (obj->coord->z - ray->origin.z) * obj->vector->z;
// 	printf("2,");
//     double denominator = ray->direction.x * obj->vector->x
//                           + ray->direction.y * obj->vector->y
//                           + ray->direction.z * obj->vector->z;
// 	printf("3,");
// 	if (denominator == 0)
// 		return (false);
// 	printf("4,");
//     double t = numerator / denominator;
//     printf("5,");
//     // Step 4: Calculate the coordinates of the intersection point
//     double intersection_x = ray->origin.x + t * ray->direction.x;
//     double intersection_y = ray->origin.y + t * ray->direction.y;
//     double intersection_z = ray->origin.z + t * ray->direction.z;
//     printf("6,");
//     // Step 5: Check if the intersection point lies on the lateral surface of the cylinder
//     double dx = intersection_x - obj->coord->x;
//     double dy = intersection_y - obj->coord->y;
//     double dz = intersection_z - obj->coord->z;
// 	printf("7,");
//     double dot_product = dx * obj->vector->x + dy * obj->vector->y + dz * obj->vector->z;
// 	printf("8,");
//     double projection_x = obj->coord->x + dot_product * obj->vector->x;
//     double projection_y = obj->coord->y + dot_product * obj->vector->y;
//     double projection_z = obj->coord->z + dot_product * obj->vector->z;
// 	printf("9,");
//     double dist = sqrt(pow(intersection_x - projection_x, 2)
//                        + pow(intersection_y - projection_y, 2)
//                        + pow(intersection_z - projection_z, 2));
// 	printf("10\n");
//     if (dist <= obj->radius && projection_x >= obj->coord->x - obj->hei_fov / 2
//         && projection_x <= obj->coord->x + obj->hei_fov / 2) {
//         return true;
//     } else {
//         return false; // No intersection or intersection not on the lateral surface of the cylinder
//     }
// }

//  double intersection_x = ray_origin_x + t * ray_dir_norm_x;
//     double intersection_y = ray_origin_y + t * ray_dir_norm_y;
//     double intersection_z = ray_origin_z + t * ray_dir_norm_z;
    
//     // Step 5: Check if the intersection point lies on the lateral surface of the cylinder
//     double dx = intersection_x - cylinder_center_x;
//     double dy = intersection_y - cylinder_center_y;
//     double dz = intersection_z - cylinder_center_z;
// 	d = substract_vector(intersection, cylinder_center);
// 	f = scalar_vector(d, cylinder_axis);
// 	p = add_vector(cylinder_center, factor_mult_vector(cylinder_axis, f));
//     double projection_x = cylinder_center_x + (f) * cylinder_axis_x;
//     double projection_y = cylinder_center_y + (f) * cylinder_axis_y;
//     double projection_z = cylinder_center_z + (f) * cylinder_axis_z;