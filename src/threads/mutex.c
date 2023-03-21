/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:00:24 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/21 16:13:05 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	create_mutexes(t_data *data)
{
	// int	i;

	// i = 0;
	// while (i < NOT)
	// {
		if (pthread_mutex_init(&data->lock, NULL) != 0)
			return (error_message(18), 1);
	// 	i++;
	// }
	return (0);
}

int	remove_mutexes(t_data *data)
{
	// int	i;

	// i = 0;
	// while (i < NOT)
	// {
		if (pthread_mutex_destroy(&data->lock) != 0)
			return (error_message(19), 1);
	// 	i++;
	// }
	return (0);
}
