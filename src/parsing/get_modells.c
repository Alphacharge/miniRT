/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_modells.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:50 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/06 18:18:29 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_sphere(t_obj *obj, char **split)
{
	char **tmp;

	if (split[1] && !pre_field_check(split[1]))
		printf("Sphere Position (%s) Syntax Error\n", split[1]);
	if (split[2] && !value_check(split[2]))
		printf("Sphere Diameter (%s) is not valid\n", split[2]);
	if (split[3] && !pre_field_check(split[3]))
		printf("Sphere Color (%s) Syntax Error\n", split[3]);
	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = SPHERE;
		tmp = ft_split_p(split[1], ',');
		if (vector_check(POS, tmp, obj->type))
			obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		obj->rad_rat = ft_atof(split[2]) / 2;
		tmp = ft_split_p(split[3], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->color = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
	}
	else
	{
		obj->type = -1;
		printf("Sphere Syntax Error\n");
	}
}

void	get_pln(t_obj *obj, char **split)
{
	char **tmp;

	if (split[1] && !pre_field_check(split[1]))
		printf("Plane Position (%s) Syntax Error\n", split[1]);
	if (split[2] && !pre_field_check(split[2]))
		printf("Plane Vector (%s) Syntax Error\n", split[2]);
	if (split[3] && !pre_field_check(split[3]))
		printf("Plane Color (%s) Syntax Error\n", split[3]);
	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = PLN;
		tmp = ft_split_p(split[1], ',');
		if (vector_check(POS, tmp, obj->type))
			obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		tmp = ft_split_p(split[2], ',');
		if (vector_check(ORI, tmp, obj->type))
			obj->vector = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
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
		printf("Plane Syntax Error\n");
	}
}

void	get_cyl(t_obj *obj, char **split)
{
	char **tmp;

	if (split[1] && !pre_field_check(split[1]))
		printf("Cylinder Position (%s) Syntax Error\n", split[1]);
	if (split[2] && !pre_field_check(split[2]))
		printf("Cylinder Vector (%s) Syntax Error\n", split[2]);
	if (split[3] && !value_check(split[3]))
		printf("Cylinder Diameter (%s) is not valid\n", split[3]);
	if (split[4] && !value_check(split[4]))
		printf("Cylinder Height (%s) is not valid\n", split[4]);
	if (split[5] && !pre_field_check(split[5]))
		printf("Cylinder Color (%s) Syntax Error\n", split[5]);
	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = CYL;
		tmp = ft_split_p(split[1], ',');
		if (vector_check(POS, tmp, obj->type))
			obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		tmp = ft_split_p(split[2], ',');
		if (vector_check(ORI, tmp, obj->type))
			obj->vector = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		obj->rad_rat = ft_atof(split[3]);
		obj->hei_fov = ft_atof(split[4]);
		tmp = ft_split_p(split[5], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->color = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
	}
	else
	{
		obj->type = -1;
		printf("Cylinder Syntax Error\n");
	}
}
