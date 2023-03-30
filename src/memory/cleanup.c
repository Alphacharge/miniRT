/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:51:35 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/30 18:57:28 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	refresh_cam(t_data *data, int casse)
{
	cancel_threads(data);
	remove_threads(data, 1);
	if (casse == 1)
		data->cam->origin.x += STEPSIZE;
	if (casse == 2)
		data->cam->origin.x -= STEPSIZE;
	if (casse == 3)
		data->cam->origin.y -= STEPSIZE;
	if (casse == 4)
		data->cam->origin.y += STEPSIZE;
	if (casse == 5)
		data->cam->origin.z += STEPSIZE;
	if (casse == 6)
		data->cam->origin.z -= STEPSIZE;
	if (casse == 7)
		get_next_cam(data);
	if (new_thread_run(data) != 0)
		cleanup(data, 4);
}

void	escape(t_data *data)
{
	cancel_threads(data);
	remove_threads(data, 0);
	if (MLX == true)
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

void	free_map(t_map *map)
{
	int	i;

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
	if (lvl > 0)
		clean_obj(data->obj);
	if (lvl > 1 && MLX == true)
		mlx_terminate(data->mlx);
	if (lvl > 2)
		ft_free(data->cam);
	ft_free(data);
	if (lvl > 3)
		exit(1);
}
