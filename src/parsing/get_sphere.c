/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:13:14 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/17 15:22:32 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_sphere(t_obj *obj, char **split)
{
	char	**tmp;

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
			obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), \
			ft_atof(tmp[2]));
		free(tmp);
		obj->radius = ft_atof(split[2]) / 2;
		tmp = ft_split_p(split[3], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->color = new_vector(ft_atof(tmp[0]) / 255.0, ft_atof(tmp[1]) / 255.0, ft_atof(tmp[2]) / 255.0);
		free(tmp);
	}
	else
		print_syntax_error(obj, "Sphere");
}
