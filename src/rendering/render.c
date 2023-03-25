/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:36:08 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/25 17:52:01 by fkernbac         ###   ########.fr       */
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
void	soft_shadow(t_thread *thread, t_ray *ray, t_vec *ambient, t_vec *image)
{
	int		col;
	int		row;
	t_vec	color;
	int		i;

	i = 0;
	row = 0;
	while (row < thread->data->height)
	{
		pthread_testcancel();
		col = thread->id - 1;
		while (col < thread->data->width)
		{
			ray = random_ray(ray, thread->cam, col, row);
			color = ray_color(ray, thread->obj, MAX_DEPTH);
			image[i] = factor_mult_vector(image[i], thread->runs);
			color = add_vector(image[i], color);
			color = factor_div_vector(color, thread->runs + 1);
			image[i++] = color;
			color = add_vector(color, *ambient);
			put_pixel(thread->img, col, row, color);
			col += NOT;
		}
		row++;
	}
}

/*Will calculate the scene with only direct light and hard shadows.*/
void	hard_shadow(t_thread *thread, t_ray *ray, t_vec *ambient, t_vec *image)
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
			ray = set_ray(ray, thread->cam, col, row);
			color = ray_at_light(ray, thread->obj, first_light(thread->obj));	//could enter a loop for all lights here
			// image[i++] = color;
			image[i++] = color_clamp(color);	//clamping seems necessary
			color = add_vector(color, *ambient);
			put_pixel(thread->img, col, row, color);
			col += NOT;
		}
		row++;
	}
}

/*Thread will render its columns until program shutdown.*/
void	*thread_routine(void *threads)
{
	t_thread	*thread;
	t_ray		*ray;
	t_vec		*ambient;
	t_vec		*image;

	thread = (t_thread *)threads;
	ray = cam_ray(thread->cam);
	ambient = get_ambient_lighting(thread->obj);
	image = ft_calloc(sizeof(t_vec), (thread->data->width / NOT + (thread->data->width % NOT) / thread->id) * thread->data->height);
	if (ray == NULL || ambient == NULL || image == NULL)
		return (ft_free(ray), ft_free(ambient), ft_free(image));
	ray->seed = xslcg_random(ray->seed + thread->id);
	hard_shadow(thread, ray, ambient, image);
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	while (SOFT_SHADOW == true)
	{
		thread->runs++;
		soft_shadow(thread, ray, ambient, image);
		ray->seed = xslcg_random(ray->seed + mlx_get_time());
	}
	ft_free(ambient);
	ft_free(ray);
	free(image);
	return (NULL);
}
