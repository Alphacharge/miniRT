/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:42:25 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/24 20:28:21 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	new_ray(void)
{
	t_ray	ray;

	ray.closest_object = NULL;
	ray.closest_t = T_MAX;
	ray.direction.x = 0;
	ray.direction.y = 0;
	ray.direction.z = 0;
	ray.origin.x = 0;
	ray.origin.y = 0;
	ray.origin.z = 0;
	ray.normal.x = 0;
	ray.normal.y = 0;
	ray.normal.z = 0;
	return (ray);
}

t_vec	point_at(t_ray ray, double t)
{
	t_vec	product;
	t_vec	target;

	product = factor_mult_vector(ray.direction, t);
	target = add_vector(ray.origin, product);
	return (target);
}

bool	front_facing(t_ray ray)
{
	if (scalar_vector(ray.direction, ray.normal) >= 0)
		return (false);
	return (true);
}

/*I pretend the light is a small sphere.
Could also calculate it as plane intersection
within radius of light coordinates.*/
bool	hit_light(t_ray *ray, t_obj *obj)
{
	return (hit_sphere(ray, obj));
}

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

	bounce = new_ray();
	if (depth <= 0)
		return (new_vector(0, 0, 0));
	if (hit_object(ray, obj) == true)
	{
		if (ray->closest_object->type == LIGHT)
			return (ray->closest_object->color);
		bounce.origin = point_at(*ray, ray->closest_t);
		target = add_vector(bounce.origin, rand_in_hemisphere(ray->seed, ray->normal));
		// target = add_vector(bounce.origin, add_vector(ray->normal, factor_mult_vector(rand_in_hemisphere(ray->seed, ray->normal), REFLEXION)));
		ray->seed = lcg_random(ray->seed);
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

t_vec	lambert_color(t_vec light_color, t_vec object_color, t_vec face_normal, t_vec to_light)
{
	t_vec	color;
	t_vec	attenuation;

	attenuation = factor_mult_vector(object_color, ALBEDO);
	color = multiply_vector(attenuation, light_color);
	// color = multiply_vector(object_color, light_color);
	color = color_clamp(color);
	color = factor_mult_vector(color, sin(scalar_vector(face_normal, to_light)));
	return (color);
}

t_vec	ray_at_light(t_ray *ray, t_obj *obj, t_obj *light, int depth)
{
	t_ray		bounce;

	bounce = new_ray();
	if (depth <= 0)
		return (new_vector(0, 0, 0));
	if (hit_object(ray, obj) == true)
	{
		if (ray->closest_object->type == LIGHT)
			return (ray->closest_object->color);
		bounce.origin = point_at(*ray, ray->closest_t);
		bounce.direction = unit_vector(subtract_vector(light->origin, bounce.origin));
		if (scalar_vector(bounce.direction, ray->normal) < 0)
			return (new_vector(0, 0, 0));
		if (front_facing(*ray) == true)
			return (lambert_color(ray_at_light(&bounce, obj, light, depth - 1), ray->closest_object->color, ray->normal, bounce.direction));
		else
			return (new_vector(0, 1, 0));
	}
	if (SKY == true)
		return (gradient(ray));
	return (new_vector(0, 0, 0));
}
