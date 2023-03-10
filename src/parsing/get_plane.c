/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:13:05 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/10 11:10:16 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_pln(t_obj *obj, char **split)
{
	char	**tmp;

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
			obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), \
			ft_atof(tmp[2]));
		free(tmp);
		tmp = ft_split_p(split[2], ',');
		if (vector_check(ORI, tmp, obj->type))
			obj->vector = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), \
			ft_atof(tmp[2]));
		print_vector(*obj->vector);
		free(tmp);
		obj->radius = ft_atof(split[2]);
		tmp = ft_split_p(split[3], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->color = new_vector(ft_atof(tmp[0]) / 255.0, ft_atof(tmp[1]) / 255.0, ft_atof(tmp[2]) / 255.0);
		free(tmp);
		//needs a check for normalized value
	}
	else
		print_syntax_error(obj, "Plane");
}
