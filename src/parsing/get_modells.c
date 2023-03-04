/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_modells.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:50 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/04 14:41:37 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_sphere(t_obj *obj, char **split)
{
	char **tmp;

	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = SPHERE;
		tmp = ft_split_p(split[1], ',');
		obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		obj->rad_rat = ft_atof(split[2]) / 2;
		tmp = ft_split_p(split[3], ',');
		obj->color = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
	}
	else
		obj->type = -1;
}

void	get_pln(t_obj *obj, char **split)
{
	char **tmp;

	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = PLN;
		tmp = ft_split_p(split[1], ',');
		obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		tmp = ft_split_p(split[2], ',');
		obj->vector = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		obj->dia_rat = ft_atof(split[2]);
		tmp = ft_split_p(split[3], ',');
		obj->color = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
	}
	else
		obj->type = -1;
}

void	get_cyl(t_obj *obj, char **split)
{
	char **tmp;

	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = CYL;
		tmp = ft_split_p(split[1], ',');
		obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		tmp = ft_split_p(split[2], ',');
		obj->vector = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		obj->dia_rat = ft_atof(split[3]);
		obj->hei_fov = ft_atof(split[4]);
		tmp = ft_split_p(split[5], ',');
		obj->color = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
	}
	else
		obj->type = -1;
}
