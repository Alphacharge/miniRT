/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:12:54 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/07 13:21:56 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_cyl(t_obj *obj, char **split)
{
	char	**tmp;

//maybe following part outsourcing in a seperate function
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
		//until here
	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = CYL;
		tmp = ft_split_p(split[1], ',');
		if (vector_check(POS, tmp, obj->type))
			obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), \
			ft_atof(tmp[2]));
		free(tmp);
		tmp = ft_split_p(split[2], ',');
		if (vector_check(ORI, tmp, obj->type))
			obj->vector = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), \
			ft_atof(tmp[2]));
		free(tmp);
		obj->rad_rat = ft_atof(split[3]);
		obj->hei_fov = ft_atof(split[4]);
		tmp = ft_split_p(split[5], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->color = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), \
			ft_atof(tmp[2]));
		free(tmp);
	}
	else
		print_syntax_error(obj, "Cylinder");
}
