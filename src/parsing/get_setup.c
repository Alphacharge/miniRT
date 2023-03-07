/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:44:55 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/06 17:43:28 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_reso(t_obj *obj, char **split)
{
	if (split[1] && !ft_strisdigit(split[1]))
		printf("Resolution Width (%s) is not valid\n", split[1]);
	if (split[2] && !ft_strisdigit(split[2]))
		printf("Resolution Height (%s) is not valid\n", split[2]);
	if (obj && split && split[1] && split[2])
	{
		obj->type = RES;
		obj->rad_rat = ft_atof(split[1]);
		obj->hei_fov = ft_atof(split[2]);
	}
	else
	{
		obj->type = -1;
		printf("Resolution Syntax Error\n");
	}
}

void	get_cam(t_obj *obj, char **split)
{
	char	**tmp;

	if (split[1] && !pre_field_check(split[1]))
		printf("Camera Position (%s) Syntax Error\n", split[1]);
	if (split[2] && !pre_field_check(split[2]))
		printf("Camera Vector (%s) Syntax Error\n", split[2]);
	if (split[3] && !ft_strisdigit(split[3]))
		printf("Camera FOV (%s) is not valid\n", split[3]);
	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = CAM;
		tmp = ft_split_p(split[1], ',');
		if (vector_check(POS, tmp, obj->type))
			obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		tmp = ft_split_p(split[2], ',');
		if (vector_check(ORI, tmp, obj->type))
			obj->vector = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		obj->hei_fov = ft_atof(split[3]) * M_PI / 180;
	}
	else
	{
		obj->type = -1;
		printf("Camera Syntax Error\n");
	}
}

void	get_ambi(t_obj *obj, char **split)
{
	char **tmp;

	if (split[1] && !value_check(split[1]))
		printf("Ambientlight Ratio is not valid\n");
	if (split[2] && !pre_field_check(split[2]))
		printf("Ambientlight Color Syntax Error\n");
	if (obj && split && split[1] && split[2])
	{
		obj->type = AMBI;
		obj->rad_rat = ft_atof(split[1]);
		tmp = ft_split_p(split[2], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
	}
	else
	{
		obj->type = -1;
		printf("Ambientlight Syntax Error\n");
	}
}

void	get_light(t_obj *obj, char **split)
{
	char **tmp;

	if (split[1] && !pre_field_check(split[1]))
		printf("Light Position Syntax Error\n");
	if (split[2] && !value_check(split[2]))
		printf("Light Ratio is not valid\n");
	if (split[3] && !pre_field_check(split[3]))
		printf("Light Color Syntax Error\n");
	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = LIGHT;
		tmp = ft_split_p(split[1], ',');
		if (vector_check(POS, tmp, obj->type))
			obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		obj->rad_rat = ft_atof(split[2]);
		tmp = ft_split_p(split[3], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->color = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
	}
	else
	{
		obj->type = -1;
		printf("Light Syntax Error\n");
	}
}
