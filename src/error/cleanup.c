/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:51:35 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/22 15:27:32 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	escape(t_data *data)
{
	// data->run = false;
	cancel_threads(data);
	remove_threads(data);
	sleep(NOT);
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

void free_map(t_map *map)
{
	int i;

	i = 0;
	while (map && map->file && map->file[i])
	{
		ft_free(map->file[i]);
		i++;
	}
	if (map->file)
		ft_free(map->file);
	if (map)
		ft_free(map);
}

void	cleanup(t_data *data, int lvl)
{
	remove_mutexes(data);
	if (lvl > 0)
		clean_obj(data->obj);
	if (lvl > 1)
		mlx_terminate(data->mlx);
	if (lvl > 2)
		ft_free(data->cam);
	ft_free(data);
}
