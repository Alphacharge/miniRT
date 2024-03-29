/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:59:51 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/03 11:13:22 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*prints the map seperated with | symbols*/
void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (map && map->file && map->file[i])
	{
		ft_putstr_fd(map->file[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}
