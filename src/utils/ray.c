/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:42:25 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/20 16:31:30 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	new_ray()
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
	const double	albedo = 0.9999;
	t_vec			attenuation;
	t_vec			color;

	attenuation = factor_mult_vector(object_color, albedo);
	color = multiply_vector(attenuation, bounce_color);
	return (color);
}

/*Sphere sampling:

Hemisphere sampling:

*/
t_vec	ray_color(t_ray *ray, t_obj *obj, int depth)
{
	t_vec		target;
	double		t;
	t_ray		bounce;
	static int	seed = (int)883082594;

	bounce = new_ray();
	if (depth <= 0)
		return (color_to_vector(0x000000FF));
	if (hit_object(ray, obj) == true)
	{
		if (ray->closest_object->type == LIGHT)
			return (ray->closest_object->color);
		// bounce.origin = point_at(*ray, ray->closest_t);
		// target = add_vector(bounce.origin, ray->normal);
		// seed = lcg_random(seed);
		// target = add_vector(target, unit_vector(rand_in_unit_sphere(seed)));
		// bounce.direction = subtract_vector(target, bounce.origin);

		bounce.origin = point_at(*ray, ray->closest_t);
		target = add_vector(bounce.origin, rand_in_hemisphere(seed, ray->normal));
		seed = lcg_random(seed);
		bounce.direction = unit_vector(subtract_vector(target, bounce.origin));
		if (front_facing(*ray) == true)
			return (combine_colors(ray_color(&bounce, obj, depth - 1), ray->closest_object->color));
		else
			return (color_to_vector(0x00FF00FF));
	}
	t = 0.5 * (unit_vector(ray->direction).y + 1.0);
	return (add_vector(factor_mult_vector(color_to_vector(0x5588FFFF), 1 - t),
		factor_mult_vector(color_to_vector(0xFFFFFFFF), t)));
	// return (color_to_vector(0x000000FF));
}

/*
camera shoots ray
if ray hits object, recursion, else return black

shoot a ray to every light source
if the face normal and the ray differ more than 90 degree, the ray cannot hit the light
*/

t_vec	hard_shadows(t_ray *ray, t_obj *obj, int depth)
{
	t_obj	*current;
	t_ray	light;
	t_vec	color;

	current = obj;
	if (depth <= 0)
		return (color_to_vector(0x000000FF));
	if (hit_object(ray, obj) == true)
	{
		color = ray->closest_object->color;
		while (current != NULL)
		{
			if (current->type == LIGHT)
			{
				light = new_ray();
				light.direction = unit_vector(subtract_vector(obj->origin, point_at(*ray, ray->closest_t)));
				if (scalar_vector(ray->normal, light.direction) > 0)
					color = combine_colors(hard_shadows(&light, obj, depth - 1), color);
			}
			current = current->next;
		}
		return (color);
	}
	return (color_to_vector(0x000000FF));
}
