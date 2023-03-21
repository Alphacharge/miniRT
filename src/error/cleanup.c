/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:51:35 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/21 16:39:41 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	escape(t_data *data)
{
	// data->run = false;
	cancel_threads(data);
	remove_threads(data);
	sleep(NOT / 2);
	cleanup(data, 3);
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
	if (lvl > 1)
		mlx_terminate(data->mlx);
	if (lvl > 2)
		ft_free(data->cam);
	ft_free(data);
}