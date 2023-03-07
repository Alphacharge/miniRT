/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:38:42 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/07 10:19:39 by rbetz            ###   ########.fr       */
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
	else
		obj->type = -1;
}

static t_obj	*line_interpreter(char *line)
{
	t_obj	*obj;
	char	**split;

	obj = ft_calloc(1, sizeof(t_obj));
	if (obj == NULL)
		return (NULL);
	split = ft_split_p(line, ' ');
	if (split == NULL)
		return (obj);
	fill_obj(obj, split);
	return (free(split), obj);
}

static void free_obj(t_obj *obj)
{
	if (obj)
	{
		if (obj->coord)
			free(obj->coord);
		if (obj->color)
			free(obj->color);
		if (obj->vector)
			free(obj->vector);
		free(obj);
	}
}

/* creates a obj list from a preparsed map list*/
t_obj	*create_obj(t_map *map)
{
	t_obj	*obj;
	t_obj	*new;
	char	*line;
	int		i;

	obj = NULL;
	i = 0;
	while (map && map->file && map->file[i] != NULL)
	{
		line = map->file[i];
		new = line_interpreter(line);
		if (new != NULL && new->type == -1)
			free_obj(new);
		if (new != NULL)
		{
			if (obj != NULL)
				new->next = obj;
			obj = new;
		}
		i++;
	}
	return (obj);
}
