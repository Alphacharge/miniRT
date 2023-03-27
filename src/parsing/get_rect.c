/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:12:54 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/27 15:52:16 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_rect(t_obj *obj, char **split)
{
	char	**tmp;

	if (split[1] && !pre_field_check(split[1]))
		printf("Rectangle Position (%s) Syntax Error\n", split[1]);
	if (split[2] && !pre_field_check(split[2]))
		printf("Rectangle Length Vector (%s) Syntax Error\n", split[2]);
	if (split[3] && !value_check(split[3]))
		printf("Rectangle Length (%s) is not valid\n", split[3]);
	if (split[4] && !pre_field_check(split[4]))
		printf("Rectangle Width Vector (%s) Syntax Error\n", split[4]);
	if (split[5] && !value_check(split[5]))
		printf("Rectangle Width (%s) is not valid\n", split[5]);
	if (split[6] && !value_check(split[6]))
		printf("Rectangle Height (%s) is not valid\n", split[6]);
	if (split[7] && !pre_field_check(split[7]))
		printf("Rectangle Color (%s) Syntax Error\n", split[7]);
	if (obj && split && split[1] && split[2] && split[3] && split[4] && split[5] && split[6] && split[7])
	{
		obj->type = RECT;
		tmp = ft_split_p(split[1], ',');
		if (vector_check(POS, tmp, obj->type))
			obj->origin = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), \
			ft_atof(tmp[2]));
		free(tmp);
		tmp = ft_split_p(split[2], ',');
		if (vector_check(ORI, tmp, obj->type))
			obj->vector = unit_vector(new_vector(ft_atof(tmp[0]), \
			ft_atof(tmp[1]), ft_atof(tmp[2])));
		free(tmp);
		obj->radius = ft_atof(split[3]);
		tmp = ft_split_p(split[4], ',');
		if (vector_check(ORI, tmp, obj->type))
			obj->vector2 = unit_vector(new_vector(ft_atof(tmp[0]), \
			ft_atof(tmp[1]), ft_atof(tmp[2])));
		free(tmp);
		obj->width = ft_atof(split[5]);
		obj->hei_fov = ft_atof(split[6]);
		tmp = ft_split_p(split[7], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->color = new_vector(ft_atof(tmp[0]) / 255.0, \
			ft_atof(tmp[1]) / 255.0, ft_atof(tmp[2]) / 255.0);
		free(tmp);
		get_square(obj, 1);
		get_square(obj, -1);
		get_square(obj, 2);
		get_square(obj, -2);
		get_square(obj, 3);
		get_square(obj, -3);
	}
	else
		print_syntax_error(obj, "Rectangle");
}
