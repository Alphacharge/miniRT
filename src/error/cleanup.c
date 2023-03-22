/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:51:35 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/22 12:29:48 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	escape(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	data->run = false;
	pthread_mutex_unlock(&data->lock);
	// cancel_threads(data);
	// remove_threads(data);
	// sleep(NOT / 2);
	// cleanup(data, 3);
	mlx_close_window(data->mlx);
}

void	clean_obj(t_obj *obj)
{
	t_obj	*tmp;

	if (obj == NULL)
		return ;
	if (obj && obj->next == NULL)
	{
		ft_free(obj);
		return ;
	}
	tmp = obj->next;
	while (obj && tmp)
	{
		ft_free(obj);
		obj = tmp;
		tmp = tmp->next;
	}
	ft_free(obj);
}

void	cleanup(t_data *data, int lvl)
{
	remove_mutexes(data);
	if (lvl > 0)
		clean_obj(data->obj);
	if (lvl > 1 && MLX == true)
		mlx_terminate(data->mlx);
	if (lvl > 2)
		ft_free(data->cam);
	ft_free(data);
}
