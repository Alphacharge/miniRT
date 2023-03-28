/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:13:05 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/28 16:43:22 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_pln(t_obj *obj, char **split)
{
	char	**tmp;

	if (obj && split && split[1] && split[2] && split[3])
	{
		pre_check(obj, "Plane Position", 1, split[1]);
		pre_check(obj, "Plane Vector", 1, split[2]);
		pre_check(obj, "Plane Color", 1, split[3]);
		if (obj->type != -1)
			obj->type = PLN;
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
		obj->radius = ft_atof(split[2]);
		tmp = ft_split_p(split[3], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->color = new_vector(ft_atof(tmp[0]) / 255.0, ft_atof(tmp[1]) \
			/ 255.0, ft_atof(tmp[2]) / 255.0);
		free(tmp);
	}
	else
		print_syntax_error(obj, "Plane");
}
//colors auf valid checken, koennen gerade ueber 255 sein
