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
	else
	{
		printf("Invalid Object key!\n");
		obj->type = -1;
	}
}

static int fill_cyl_obj(t_obj **obj, char **split, int i) {
	t_obj	*newobj;
	int		j;

	j = 0;
	newobj = ft_calloc(3, sizeof(t_obj));
	if (newobj == NULL)
		return (error_message(10), -1);
	get_cyl(&newobj[j], split);
	obj[i + j] = &newobj[j];
	j++;
	get_circle(obj[i], &newobj[j], obj[i]->vector);
	obj[i + j] = &newobj[j];
	j++;
	get_circle(obj[i], &newobj[j], invert_vector(obj[i]->vector));
	obj[i + j] = &newobj[j];
	j++;
	return 1;
}

static int fill_rect_obj(t_obj **obj, char **split, int i) {
	t_obj	*newobj_squares[6];
	t_obj	*newobj_rect;
	int		j;
	int		k;

	j = 0;
	k = 0;
	newobj_rect = ft_calloc(1, sizeof(t_obj));
	if (newobj_rect == NULL)
		return (error_message(10), -1);
	get_rect(newobj_rect, newobj_rect, split, 1);
	obj[i] = newobj_rect;
	while (j < 6) {
		newobj_squares[j] = ft_calloc(1, sizeof(t_obj));
		if (newobj_squares[j] == NULL) {
			while (k < j) {
				ft_free(newobj_squares[k]);
				k++;
			}
			ft_free(newobj_rect);
			return (error_message(10), -1);
		}
		j++;
	}
	j = 0;
	while (j < 6) {
		get_rect(newobj_rect, newobj_squares[j], split, j + 2);
		obj[i + j + 1] = newobj_squares[j];
		j++;
	}
	return 1;
}

static int	line_interpreter(t_obj **obj, char *line)
{
	t_obj		*newobj;
	char		**split;
	static int	i;

	newobj = NULL;
	split = ft_split_p(line, ' ');
	if (split == NULL)
		return (error_message(11), ft_free(newobj), -1);
	if (!ft_strcmp(split[0], "R") || !ft_strcmp(split[0], "C") || \
		!ft_strcmp(split[0], "A") || !ft_strcmp(split[0], "L") || \
		!ft_strcmp(split[0], "SP") || !ft_strcmp(split[0], "PL")) {
			newobj = ft_calloc(1, sizeof(t_obj));
			if (newobj == NULL)
				return (error_message(10), -1);
			fill_obj(newobj, split);
			obj[i] = newobj;
			i++;
	}
	else if (!ft_strcmp(split[0], "CY")) {
		fill_cyl_obj(obj, split, i);
		i += 3;
	}
	else if (!ft_strcmp(split[0], "RECT")) {
		fill_rect_obj(obj, split, i);
		i += 6;
	}
	else
	{
		printf("Invalid Object key!\n");
		newobj->type = -1;
	}
	return (ft_free(split), 1);
}

static bool	check_objs(t_obj **obj)
{
	int	i;

	i = 0;
	while (obj && obj[i]) {
		if (obj[i]->type == -1) {
			printf("Error on Object Number --> %d", i);
			printf("| Origin is: (%f,%f,%f)\n", obj[i]->origin.x, \
				obj[i]->origin.y, obj[i]->origin.z);
			return (false);
		}
		i++;
	}
	return (true);
}

/* creates a obj list from a preparsed map list*/
int	create_obj(t_data *data)
{
	int	i;

	i = 0;
	while (data && data->map && i <= data->lines && data->map->file && data->map->file[i] != NULL)
	{
		if (line_interpreter(data->obj, data->map->file[i]) < 0)
			return (free_map(data->map), clean_obj(data->obj, data->map->lines), -1);
		i++;
	}
	data->lines = data->map->lines;
	free_map(data->map);
	if (!check_objs(data->obj))
		return (clean_obj(data->obj, data->lines), -1);
	return (1);
}
