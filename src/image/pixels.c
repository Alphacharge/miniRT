/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:36:08 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/03 14:15:31 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//this might be only a temporary struct
t_sphere	*new_sphere(float x, float y, float z, float radius)
{
	t_sphere	*sphere;

	sphere = ft_calloc(1, sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->center = ft_calloc(1, sizeof(t_vec));
	if (sphere->center == NULL)
		return (NULL);
	sphere->center->x = x;
	sphere->center->y = y;
	sphere->center->z = z;
	sphere->radius = radius;
	return (sphere);
}

bool	hit_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vec	origin_center;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t;
	float	length;

	origin_center = subtract_vector(ray->origin, *sphere->center);
	length = length_vector(ray->direction);
	a = pow(length, 2);
	b = scalar_vector(origin_center, ray->direction);
	length = length_vector(origin_center);
	c = pow(length, 2) - pow(sphere->radius, 2);
	discriminant = b * b - a * c;
	if (discriminant < 0)
		return (false);
	discriminant = sqrt(discriminant);
	t = (-b - discriminant) / a;
	if (t < T_MIN || T_MAX < t)
	{
		t = (-b + discriminant) / a;
		if (t < T_MIN || T_MAX < t)
			return (false);
	}
	if (t < ray->closest_t)
	{
		ray->closest_t = t;
		ray->closest_object = sphere;
	}
	ray->normal = point_at(ray, t);
	ray->normal = subtract_vector(ray->normal, *sphere->center);
	ray->normal = factor_div_vector(ray->normal, sphere->radius);
	return (true);
}

int	draw_image(mlx_image_t *img, t_cam *cam)
{
	int			col;
	int			row;
	t_ray		ray;

	col = 0;
	row = 0;
	printf("Image size: %ix%i\n", img->width, img->height);
	ray.origin.x = 0;
	ray.origin.y = 0;
	ray.origin.z = 0;
	ray.closest_t = T_MAX;
	ray.closest_object = NULL;


	t_sphere	*sphere1;
	t_sphere	*sphere2;
	sphere1 = new_sphere(50, 50, -300, 200);
	sphere2 = new_sphere(0, 0, 300, 100);




	//shoot a ray through camera origin and every pixel (image plane)
	while (row < (int)img->height)
	{
		while (col < (int)img->width)
		{
			ray.direction.x = cam->upper_left_corner->x + col;
			ray.direction.y = cam->upper_left_corner->y + row;
			ray.direction.z = cam->focal_length * -1;
			if (hit_sphere(&ray, sphere1) == true)
			// hit_sphere(&ray, sphere2);
				mlx_put_pixel(img, col, row, ray_color(&ray));
			col++;
		}
		col = 0;
		row++;
	}
	printf("Image rendered.\n");
	return (0);
}
