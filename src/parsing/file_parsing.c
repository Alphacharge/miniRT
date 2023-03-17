/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:03:38 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/17 19:39:24 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*remove spaces by copy to front the rest of the string*/
static char	*move_field(char *s)
{
	if (s == NULL)
		return (s);
	while (s[0] != '\0' && ft_isspace(s[0]))
		ft_memmove(&s[0], &s[1], ft_strlen(&s[0]));
	if (*s != '\0')
		s++;
	while (*s != '\0' && ft_isvalue(*s))
		s++;
	if (*s != '\0' && !theend(s))
		s++;
	return (s);
}

/*homogenize the string to facilitate further processing*/
static void	validate_lines(t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	while (map && map->file && map->file[i])
	{
		line = kill_nltb(map->file[i]);
		while (line[0] != '\0' && line[1] != '\0' && !ft_isalpha(line[0]))
			ft_memmove(&line[0], &line[1], ft_strlen(&line[0]));
		while (*line != '\0' && ft_isalpha(*line))
		{
			*line = ft_toupper(*line);
			line++;
		}
		line++;
		while (*line != '\0')
			line = move_field(line);
		i++;
	}
}

/*Read the input file and safe only non comments*/
static void	parse_file(t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	if (map == NULL || map->file == NULL)
		return ;
	while (1)
	{
		line = get_next_line(map->fd);
		if (line == NULL)
			break ;
		if (first_iscomment(line))
			ft_free(line);
		else
		{
			map->file[i] = line;
			i++;
		}
	}
}

/*read the inputfile and count the lines that are no comments and alloc ** */
static void	count_lines(t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(map->fd);
		if (line == NULL)
			break ;
		if (!first_iscomment(line))
			i++;
		if (line != NULL)
			ft_free(line);
	}
//this leaks
	map->file = ft_calloc(i + 1, sizeof(char *));
	if (map->file != NULL)
		map->file[i] = NULL;
}

/*Validate the input and call parsing*/
t_map	*check_input(int argc, char **argv)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->fd = -1;
	if (argc < 2)
		return (map);
	if (argc > 2)
		return (map);
	if (!ft_strcmp(argv[1], ""))
		return (map);
	map->fd = open(argv[1], O_RDONLY);
	if (map->fd < 0)
		return (map);
	count_lines(map);
	close(map->fd);
	map->fd = open(argv[1], O_RDONLY);
	parse_file(map);
	close(map->fd);
	validate_lines(map);
	return (map);
}
