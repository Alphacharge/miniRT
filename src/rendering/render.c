/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:36:08 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/31 10:53:22 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	put_pixel(mlx_image_t *img, int x, int y, t_vec color)
{
	color = color_clamp(color);
	if (img == NULL)
		return ;
	mlx_put_pixel(img, x, y, gamma_correction(color));
}

/*Returns first light object.*/
t_obj	*first_light(t_obj *list)
{
	while (list != NULL && list->type != LIGHT)
		list = list->next;
	return (list);
}

/*Will calculate the scene with stochastic sampling, GI and soft shadows.*/
void	soft_shadow(t_thread *thread, t_ray *ray, t_vec *pixels, t_data *data)
{
	int		col;
	int		row;
	t_vec	color;
	int		i;

	i = 0;
	row = 0;
	while (row < data->height)
	{
		col = thread->id - 1;
		pthread_testcancel();
		while (col < data->width)
		{
			color = new_vector(0, 0, 0);
			ray = random_ray(ray, data->cam, col, row);
			pixels[i] = factor_mult_vector(pixels[i], thread->runs);
			color = add_vector(pixels[i], ray_color(ray, data->obj, MAX_DEPTH));
			color = factor_div_vector(color, thread->runs + 1);
			pixels[i++] = color;
			color = add_vector(color, thread->ambient);
			put_pixel(data->img, col, row, color);
			col += NOT;
		}
		row++;
	}
}

/*Will calculate the scene with only direct light and hard shadows.*/
void	hard_shadow(t_thread *thread, t_ray *ray, t_vec ambient, t_vec *pixels)
{
	int		col;
	int		row;
	t_vec	color;
	int		i;

	i = 0;
	row = 0;
	while (row < thread->data->height)
	{
		col = thread->id - 1;
		while (col < thread->data->width)
		{
			color = new_vector(0, 0, 0);
			ray = set_ray(ray, thread->data->cam, col, row);
			color = ray_at_light(ray, thread->data->obj, \
				first_light(thread->data->obj));
			pixels[i++] = color;
			color = add_vector(color, ambient);
			put_pixel(thread->data->img, col, row, color);
			col += NOT;
		}
		row++;
	}
}

/*Thread will render its columns until program shutdown.*/
void	*thread_routine(void *threads)
{
	t_thread	*thread;

	thread = (t_thread *)threads;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	hard_shadow(thread, thread->ray, thread->ambient, thread->pixels);
	while (SOFT_SHADOW == true)
	{
		if (SAMPLES > 0 && thread->runs > SAMPLES)
			break ;
		thread->runs++;
		soft_shadow(thread, thread->ray, thread->pixels, thread->data);
		thread->ray->seed = xslcg_random(thread->ray->seed);
	}
	return (NULL);
}
