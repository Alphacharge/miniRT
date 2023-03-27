/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:15:39 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/27 18:00:23 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Combines the color of an incoming light ray and the object color to a
diffuse value.*/
t_vec	combine_colors(t_vec bounce_color, t_vec object_color)
{
	t_vec	attenuation;
	t_vec	color;

	attenuation = factor_mult_vector(object_color, ALBEDO);
	color = multiply_vector(attenuation, bounce_color);
	return (color);
}

/*Returns a gradient for background ("sky").*/
t_vec	gradient(t_ray *ray)
{
	double	t;
	t_vec	top_color;
	t_vec	bottom_color;

	top_color = new_vector(0.1, 0.4, 1.0);
	bottom_color = new_vector(1, 1, 1);
	t = 0.5 * (ray->direction.y + 1.0);
	top_color = factor_mult_vector(top_color, 1 - t);
	bottom_color = factor_mult_vector(bottom_color, t);
	return (add_vector(top_color, bottom_color));
}

/*I pretend the light is a small sphere.
Could also calculate it as plane intersection
within radius of light coordinates.*/
bool	hit_light(t_ray *ray, t_obj *obj)
{
	return (hit_sphere(ray, obj));
}

/*Checks if the ray hit any object in the linked list.*/
bool	hit_object(t_ray *ray, t_obj *obj)
{
	bool	hit_anything;

	hit_anything = false;
	while (obj != NULL)
	{
		if (obj->type == SPHERE && hit_sphere(ray, obj) == true)
			hit_anything = true;
		else if (obj->type == LIGHT && hit_light(ray, obj) == true)
			hit_anything = true;
		else if (obj->type == PLN && hit_plane(ray, obj) == true)
			hit_anything = true;
		else if (obj->type == CYL && hit_cylinder(ray, obj) == true)
			hit_anything = true;
		else if (obj->type == CIRCLE && hit_circle(ray, obj) == true)
			hit_anything = true;
		obj = obj->next;
	}
	return (hit_anything);
}

/*Sphere sampling:
		bounce.origin = point_at(*ray, ray->closest_t);
		target = add_vector(bounce.origin, ray->normal);
		seed = lcg_random(seed);
		target = add_vector(target, unit_vector(rand_in_unit_sphere(seed)));
		bounce.direction = subtract_vector(target, bounce.origin);
Hemisphere sampling:
		bounce.origin = point_at(*ray, ray->closest_t);
		target = add_vector(bounce.origin, rand_in_hemisphere(seed, ray->normal));
		seed = lcg_random(seed);
		bounce.direction = unit_vector(subtract_vector(target, bounce.origin));
*/
t_vec	ray_color(t_ray *ray, t_obj *obj, int depth)
{
	t_vec		target;
	t_ray		bounce;

	bounce = bounce_ray(ray);
	if (depth <= 0)
		return (new_vector(0, 0, 0));
	if (hit_object(ray, obj) == true)
	{
		if (ray->closest_object->type == LIGHT)
			return (ray->closest_object->color);
		bounce.origin = point_at(*ray, ray->closest_t);
		target = add_vector(bounce.origin, rand_in_hemisphere(ray->seed, ray->normal));
		ray->seed = xorshift_random(ray->seed);
		bounce.direction = unit_vector(subtract_vector(target, bounce.origin));
		if (front_facing(*ray) == true)
			return (combine_colors(ray_color(&bounce, obj, depth - 1), ray->closest_object->color));
		else
			return (new_vector(0, 1, 0));
	}
	if (SKY == true)
		return (gradient(ray));
	return (new_vector(0, 0, 0));
}
