/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:00:24 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/27 20:34:02 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	create_mutexes(t_data *data)
{
		if (pthread_mutex_init(&data->lock, NULL) != 0)
			return (error_message(18), 1);
	return (0);
}

int	remove_mutexes(t_data *data)
{
	if (pthread_mutex_destroy(&data->lock) != 0)
			return (error_message(19), 1);
	return (0);
}
