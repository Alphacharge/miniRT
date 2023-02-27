/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:03:38 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/27 14:31:55 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*set error and return map for 1 liner*/
static t_map	*set_error(t_map *map, int error)
{
	map->error = error;
	return (map);
}

/*remove [space][tab][nl] form beginning and end of each field*/
static void	parse_line(t_map *map)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (map->file && map->file[i])
	{
		j = 0;
		while (map->file[i] && map->file[i][j])
		{
			tmp = map->file[i][j];
			map->file[i][j] = ft_strtrim(map->file[i][j], " \t\n");
			if (map->file[i][j] == NULL)
				map->error = 9;
			free(tmp);
			j++;
		}
		i++;
	}
}

/*Read the input file line by line and realloc pointer if not big enough*/
static void	parse_file(t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	map->file = ft_calloc(map->size, sizeof(char **));
	if (map->file == NULL)
	{
		map->error = 7;
		return ;
	}
	while (1 && map->error == 0)
	{
		line = get_next_line(map->fd);
		if (line == NULL)
		{
			map->error = 8;
			break ;
		}
		if (i == map->size)
			map->size = realloc_map(map);
		map->file[i++] = ft_split(line, ' ');
		if (line != NULL)
			ft_free(line);
	}
}

/*Validate the input and call parsing*/
t_map	*parse_scene(int argc, char **argv)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map *));
	map->fd = -1;
	map->size = 10;
	map->error = 0;
	if (argc < 2)
		return (set_error(map, 3));
	if (argc > 2)
		return (set_error(map, 4));
	if (!ft_strcmp(argv[1], ""))
		return (set_error(map, 5));
	map->fd = open(argv[1], O_RDONLY);
	if (map->fd < 0)
		return (set_error(map, 6));
	parse_file(map);
	if (map->error == 0)
		parse_line(map);
	return (map);
}
