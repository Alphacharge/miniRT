/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:19:16 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/31 10:08:29 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Combines all ambient lighting of the scene.*/
t_vec	get_ambient_lighting(t_obj *obj)
{
	t_vec	ambient;

	ambient = new_vector(0, 0, 0);
	while (obj != NULL)
	{
		if (obj->type == AMBI)
			ambient = add_vector(ambient, \
				factor_mult_vector(obj->color, obj->width));
		obj = obj->next;
	}
	return (ambient);
}

int	new_thread_run(t_data *data)
{
	int	i;

	i = 0;
	while (i < NOT)
	{
		data->threads[i].runs = 1;
		data->threads[i].ray = cam_ray(data->cam);
		if (data->threads[i].ray == NULL || data->threads[i].pixels == NULL)
			return (error_message(1), 1);
		data->threads[i].ray->seed = xorshift_random(data->threads[i].ray->seed \
				+ (int)(mlx_get_time() * 1000000000) % 1000 + i);
		if (pthread_create(&data->threads[i].pid, NULL, &thread_routine, \
			(void *)&data->threads[i]) != 0)
			return (error_message(15), 1);
		i++;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < NOT)
	{
		data->threads[i].id = i + 1;
		data->threads[i].data = data;
		data->threads[i].pixels = ft_calloc(sizeof(t_vec), (data->width / NOT \
			+ (data->width % NOT) / (i + 1)) * data->height);
		data->threads[i].ambient = get_ambient_lighting(data->obj);
		i++;
	}
	return (new_thread_run(data));
}

int	remove_threads(t_data *data, int mode)
{
	int	i;

	i = 0;
	while (i < NOT && data->threads[i].pid)
	{
		if (pthread_join(data->threads[i].pid, NULL) != 0)
			return (error_message(16), 1);
		data->threads[i].pid = 0;
		ft_free(data->threads[i].ray);
		if (mode == 0)
			ft_free(data->threads[i].pixels);
		i++;
	}
	return (0);
}

int	cancel_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < NOT && data->threads[i].pid != 0)
	{
		if (pthread_cancel(data->threads[i].pid) != 0)
			return (error_message(17), 1);
		i++;
	}
	return (0);
}
