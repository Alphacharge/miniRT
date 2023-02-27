/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:00:19 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/27 14:08:50 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	realloc_map(t_map *map)
{
	char	***new;
	int		i;

	i = 0;
	new = ft_calloc(2 * map->size, sizeof(char **));
	if (new == NULL)
	{
		map->error = 9;
		return (map->size);
	}
	while (i < map->size)
	{
		new[i] = map->file[i];
		i++;
	}
	free(map->file);
	map->file = new;
	return (2 * map->size);
}
