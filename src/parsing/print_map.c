/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:59:51 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/27 14:00:02 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map && i < map->size && map->file)
	{
		j = 0;
		while (map->file[i] && map->file[i][j])
		{
			ft_putstr_fd("|", 1);
			ft_putstr_fd(map->file[i][j], 1);
			ft_putstr_fd("|\t", 1);
			j++;
		}
		ft_putstr_fd("|\n", 1);
		i++;
	}
}
