/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:36:08 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/27 18:05:16 by fkernbac         ###   ########.fr       */
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
	//placeholder function?
	while (list != NULL && list->type != LIGHT)
		list = list->next;
	return (list);
}

/*Will calculate the scene with stochastic sampling, GI and soft shadows.*/
void	soft_shadow(t_thread *thread, t_ray *ray, t_vec *ambient, t_vec *pixels)
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
		pthread_testcancel();
		while (col < thread->data->width)
		{
			ray = random_ray(ray, thread->data->cam, col, row);
			color = ray_color(ray, thread->data->obj, MAX_DEPTH);
			pixels[i] = factor_mult_vector(pixels[i], thread->runs);
			color = add_vector(pixels[i], color);
			color = factor_div_vector(color, thread->runs + 1);
			pixels[i++] = color;
			color = add_vector(color, *ambient);
			put_pixel(thread->data->img, col, row, color);
			col += NOT;
		}
		row++;
	}
}

/*Will calculate the scene with only direct light and hard shadows.*/
void	hard_shadow(t_thread *thread, t_ray *ray, t_vec *ambient, t_vec *pixels)
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
			ray = set_ray(ray, thread->data->cam, col, row);
			color = ray_at_light(ray, thread->data->obj, first_light(thread->data->obj));	//could enter a loop for all lights here
			// pixels[i++] = color;
			pixels[i++] = color_clamp(color);	//clamping seems necessary
			color = add_vector(color, *ambient);
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
	hard_shadow(thread, thread->ray, thread->ambient, thread->pixels);
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	while (SOFT_SHADOW == true)
	{
		thread->runs++;
		soft_shadow(thread, thread->ray, thread->ambient, thread->pixels);
		thread->ray->seed = xslcg_random(thread->ray->seed + (int)&thread->ambient);
		// if (thread->runs % 10 == 0)
		// 	printf("%i: run %i\n", thread->id, thread->runs);
	}
	return (NULL);
}
