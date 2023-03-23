/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:36:08 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/23 11:02:27 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	color_clamp(t_vec color)
{
	if (color.x > 1)
		color.x = 1;
	else if (color.x < 0)
		color.x = 0;
	if (color.y > 1)
		color.y = 1;
	else if (color.y < 0)
		color.y = 0;
	if (color.z > 1)
		color.z = 1;
	else if (color.z < 0)
		color.z = 0;
	return (color);
}

void	put_pixel(mlx_image_t *img, int x, int y, t_vec color)
{
	color = color_clamp(color);
	if (img == NULL)
		return ;
	mlx_put_pixel(img, x, y, gamma_correction(color));
}

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
	return (ray);
}

t_ray	*random_ray(t_ray *ray, t_cam *cam, int col, int row)
{
	double				x;
	double				y;

	ray->seed = lcg_random(ray->seed);
	x = (double)col + random_double(ray->seed);
	ray->seed = xorshift_random(ray->seed);
	y = (double)row + random_double(ray->seed);
	ray->direction = factor_mult_vector(cam->horizontal, x);
	ray->direction = add_vector(ray->direction, factor_mult_vector(cam->vertical, y));
	ray->direction = add_vector(cam->upper_left_corner, ray->direction);
	ray->direction = unit_vector(ray->direction);
	ray->closest_t = T_MAX;
	ray->closest_object = NULL;
	return (ray);
}

t_ray	*set_ray(t_ray *ray, t_cam *cam, int col, int row)
{
	double	x;
	double	y;

	x = (double)col;
	y = (double)row;
	ray->direction = factor_mult_vector(cam->horizontal, x);
	ray->direction = add_vector(ray->direction, factor_mult_vector(cam->vertical, y));
	ray->direction = add_vector(cam->upper_left_corner, ray->direction);
	ray->direction = unit_vector(ray->direction);
	ray->closest_t = T_MAX;
	ray->closest_object = NULL;
	return (ray);
}

t_vec	*get_ambient_lighting(t_obj *obj)
{
	t_vec	ambient;
	t_vec	*allocate;

	ambient.x = 0;
	ambient.y = 0;
	ambient.z = 0;
	while (obj != NULL)
	{
		if (obj->type == AMBI)
			ambient = add_vector(ambient, obj->color);
		obj = obj->next;
	}
	allocate = ft_calloc(1, sizeof(t_vec));
	if (allocate == NULL)
		return (NULL);
	allocate->x = ambient.x;
	allocate->y = ambient.y;
	allocate->z = ambient.z;
	return (allocate);
}

t_obj	*first_light(t_obj *list)
{
	while (list != NULL && list->type != LIGHT)
		list = list->next;
	return (list);
}

void	draw_image(t_thread *thread, t_ray *ray, t_vec *ambient)
{
	int		col;
	int		row;
	int		i;
	t_vec	color;

	row = 0;
	while (row < thread->data->height)
	{
		col = thread->id - 1;
		while (col < thread->data->width)
		{
			pthread_testcancel();
			color = new_vector(0, 0, 0);
			i = 0;
			while (++i < SAMPLES)
				color = add_vector(color, ray_color(random_ray(ray, thread->cam, col, row), thread->obj, MAX_DEPTH));
//following line uses one sample to calculate hard shadow of first light
			color = add_vector(color, factor_mult_vector(ray_at_light(set_ray(ray, thread->cam, col, row), thread->obj, first_light(thread->obj), MAX_DEPTH), SHADOW));
			color = factor_mult_vector(color, 1.0 / (double)SAMPLES);
			color = add_vector(color, *ambient);
			pthread_testcancel();
			put_pixel(thread->img, col, row, color);
			col += NOT;
		}
		row++;
	}
}

void	*thread_routine(void *threads)
{
	t_ray			*ray;
	t_vec			*ambient;
	t_thread		*thread;

	thread = (t_thread *)threads;
	ray = cam_ray(thread->cam);
	ray->seed = xorshift_random(ray->seed - thread->id);
	ambient = get_ambient_lighting(thread->obj);
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	draw_image(thread, ray, ambient);
	ft_free(ambient);
	ft_free(ray);
	// pthread_exit(NULL);
	return (NULL);
}
