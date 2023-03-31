/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:42:25 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/31 12:49:11 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	bounce_ray(t_ray *original)
{
	t_ray	ray;

	ray.closest_object = NULL;
	ray.closest_t = T_MAX;
	ray.direction = new_vector(0, 0, 0);
	ray.origin = new_vector(0, 0, 0);
	ray.normal = new_vector(0, 0, 0);
	ray.seed = original->seed;
	return (ray);
}

/*Returns true if ray and normal face each other.*/
bool	front_facing(t_vec ray_direction, t_vec face_normal)
{
	if (scalar_vector(ray_direction, face_normal) >= 0)
		return (false);
	return (true);
}

/*Shoots ray through pixel col|row.*/
t_ray	*set_ray(t_ray *ray, t_cam *cam, double col, double row)
{
	ray->direction = new_vector(0, 0, 0);
	ray->direction = add_vector(\
		factor_mult_vector(cam->horizontal, col), \
		factor_mult_vector(cam->vertical, row));
	ray->direction = add_vector(cam->upper_left_corner, ray->direction);
	ray->direction = unit_vector(ray->direction);
	ray->closest_t = T_MAX;
	ray->closest_object = NULL;
	return (ray);
}

/*Shoots ray through random point withing pixel col|row.*/
t_ray	*random_ray(t_ray *ray, t_cam *cam, int col, int row)
{
	double	rand_x;
	double	rand_y;

	ray->seed = xorshift_random(ray->seed);
	rand_x = (double)col + random_double(ray->seed);
	ray->seed = xorshift_random(ray->seed);
	rand_y = (double)row + random_double(ray->seed);
	ray = set_ray(ray, cam, rand_x, rand_y);
	return (ray);
}

/*Sets common values used for all rays starting from camera.*/
t_ray	*cam_ray(t_cam *cam)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	if (ray == NULL)
		return (NULL);
	ray->origin = cam->origin;
	ray->closest_t = T_MAX;
	ray->closest_object = NULL;
	ray->seed = 883082594;
	ray->normal = new_vector(0, 0, 0);
	ray->direction = new_vector(0, 0, 0);
	return (ray);
}
