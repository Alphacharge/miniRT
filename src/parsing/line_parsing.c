/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:38:42 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/31 10:21:32 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	fill_obj(t_obj	*obj, char **split)
{
	if (!ft_strcmp(split[0], "R"))
		get_reso(obj, split);
	else if (!ft_strcmp(split[0], "C"))
		get_cam(obj, split);
	else if (!ft_strcmp(split[0], "A"))
		get_ambi(obj, split);
	else if (!ft_strcmp(split[0], "L"))
		get_light(obj, split);
	else if (!ft_strcmp(split[0], "SP"))
		get_sphere(obj, split);
	else if (!ft_strcmp(split[0], "PL"))
		get_pln(obj, split);
	else if (!ft_strcmp(split[0], "CY"))
		get_cyl(obj, split);
	else if (!ft_strcmp(split[0], "RECT"))
		get_rect(obj, split);
	else
	{
		printf("Invalid Object key!\n");
		obj->type = -1;
	}
}

static t_obj	*line_interpreter(char *line)
{
	t_obj	*obj;
	char	**split;

	obj = ft_calloc(1, sizeof(t_obj));
	if (obj == NULL)
		return (error_message(10), NULL);
	obj->next = NULL;
	split = ft_split_p(line, ' ');
	if (split == NULL)
		return (error_message(11), ft_free(obj), NULL);
	fill_obj(obj, split);
	return (ft_free(split), obj);
}

static bool	check_objs(t_obj *obj)
{
	t_obj	*tmp;
	int		i;

	i = 1;
	tmp = obj;
	if (tmp == NULL)
		return (false);
	while (tmp != NULL)
	{
		i++;
		if (tmp->type == -1)
		{
			printf("Error on Object Number --> %d", i);
			printf("| Origin is: (%f,%f,%f)\n", tmp->origin.x, tmp->origin.y, \
				tmp->origin.z);
			return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}

/* creates a obj list from a preparsed map list*/
t_obj	*create_obj(t_map *map)
{
	t_obj	*obj;
	t_obj	*new;
	t_obj	*tmp;
	int		i;

	obj = NULL;
	i = 0;
	while (map && map->file && map->file[i] != NULL)
	{
		new = line_interpreter(map->file[i++]);
		if (new == NULL)
			return (free_map(map), clean_obj(obj), NULL);
		tmp = obj;
		if (tmp == NULL)
			obj = new;
		while (tmp && tmp->next != NULL)
			tmp = tmp->next;
		if (tmp != NULL)
			tmp->next = new;
	}
	free_map(map);
	if (!check_objs(obj))
		return (clean_obj(obj), NULL);
	return (obj);
}
