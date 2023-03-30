/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:15:39 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/30 12:41:42 by rbetz            ###   ########.fr       */
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

t_vec	bounce_color(t_ray *ray, t_ray	*bounce, t_obj *obj, int depth)
{
	t_vec	target;

	target = add_vector(bounce->origin, \
		rand_in_hemisphere(ray->seed, ray->normal));
	ray->seed = xorshift_random(ray->seed);
	bounce->direction = unit_vector(subtract_vector(target, bounce->origin));
	return (ray_color(bounce, obj, depth));
}

t_vec	bouncecolor_average(t_ray *ray, t_obj *obj, int depth)
{
	t_ray	bounce;
	t_vec	color;
	int		i;

	if (depth <= 0)
		return (new_vector(0, 0, 0));
	i = 0;
	bounce = bounce_ray(ray);
	bounce.origin = point_at(*ray, ray->closest_t);
	color = new_vector(0, 0, 0);
	while (i < BOUNCES)
	{
		color = add_vector(color, bounce_color(ray, &bounce, obj, depth));
		i++;
	}
	color = factor_div_vector(color, BOUNCES);
	return (color);
}

t_vec	ray_color(t_ray *ray, t_obj *obj, int depth)
{
	if (depth <= 0)
		return (new_vector(0, 0, 0));
	if (hit_object(ray, obj) == true)
	{
		if (ray->closest_object->type == LIGHT)
			return (ray->closest_object->color);
		if (front_facing(*ray) == true)
			return (combine_colors(bouncecolor_average(ray, obj, depth - 1), \
				ray->closest_object->color));
		else
			return (new_vector(0, 1, 0));
	}
	if (SKY == true)
		return (gradient(ray));
	return (new_vector(0, 0, 0));
}
