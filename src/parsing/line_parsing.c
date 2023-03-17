/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:38:42 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/17 17:25:28 by rbetz            ###   ########.fr       */
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

// static void	print_obj(t_obj *obj)
// {
// 	if (obj->type == -1)
// 		printf("Object is invalid\n");
// 	else if (obj->type == RES)
// 		printf("Resolution: %f x %f\n", obj->rad_rat, obj->hei_fov);
// 	else if (obj->type == CAM)
// 		printf("Camera: %f %f %f %f %f %f %f\n", obj->origin->x, obj->origin->y, obj->origin->z, obj->vector->x, obj->vector->y, obj->vector->z, obj->hei_fov);
// 	else if (obj->type == AMBI)
// 		printf("Ambient: %f %f %f %f\n", obj->rad_rat, obj->color->x, obj->color->y, obj->color->z);
// 	else if (obj->type == LIGHT)
// 		printf("Light: %f %f %f %f %f %f %f\n", obj->origin->x, obj->origin->y, obj->origin->z, obj->rad_rat, obj->color->x, obj->color->y, obj->color->z);
// 	else if (obj->type == SPHERE)
// 		printf("Sphere: %f %f %f %f %f %f %f\n", obj->origin->x, obj->origin->y, obj->origin->z, obj->rad_rat, obj->color->x, obj->color->y, obj->color->z);
// 	else if (obj->type == PLN)
// 		printf("Plane: %f %f %f %f %f %f %f %f %f\n", obj->origin->x, obj->origin->y, obj->origin->z, obj->vector->x, obj->vector->y, obj->vector->z, obj->color->x, obj->color->y, obj->color->z);
// 	else if (obj->type == CYL)
// 		printf("Cylinder: %f %f %f %f %f %f %f %f %f %f %f\n", obj->origin->x, obj->origin->y, obj->origin->z, obj->vector->x, obj->vector->y, obj->vector->z, obj->rad_rat, obj->hei_fov, obj->color->x, obj->color->y, obj->color->z);
// }
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
	// print_obj(obj);
	return (free(split), obj);
}

// void	free_obj(t_obj *obj)
// {
// 	if (obj)
// 	{
// 		if (obj->origin)
// 			free(obj->origin);
// 		if (obj->color)
// 			free(obj->color);
// 		if (obj->vector)
// 			free(obj->vector);
// 		free(obj);
// 	}
// }

/* creates a obj list from a preparsed map list*/
t_obj	*create_obj(t_map *map)
{
	t_obj	*obj;
	t_obj	*new;
	t_obj	*tmp;
	char	*line;
	int		i;

	obj = NULL;
	i = 0;
	while (map && map->file && map->file[i] != NULL)
	{
		line = map->file[i];
		new = line_interpreter(line);
		// if (new != NULL && new->type == -1)
		// 	free_obj(new); //loosing 2 obj if cylinder fails
		if (new != NULL)
		{
			tmp = new;
			while (tmp && tmp->next != NULL)
				tmp = tmp->next;
			if (obj != NULL)
				tmp->next = obj;
			obj = new;
		}
		i++;
	}
	return (obj);
}
