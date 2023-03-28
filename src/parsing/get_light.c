/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:13:00 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/28 16:41:05 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_light(t_obj *obj, char **split)
{
	char	**tmp;
	double	intensity;

	if (obj && split && split[1] && split[2] && split[3])
	{
		pre_check(obj, "Light Position", 1, split[1]);
		pre_check(obj, "Light Ratio", 2, split[2]);
		pre_check(obj, "Light Color", 1, split[3]);
		if (obj->type != -1)
			obj->type = LIGHT;
		tmp = ft_split_p(split[1], ',');
		if (vector_check(POS, tmp, obj->type))
			obj->origin = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), \
			ft_atof(tmp[2]));
		free(tmp);
		intensity = ft_atof(split[2]);
		tmp = ft_split_p(split[3], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->color = new_vector(\
				ft_atof(tmp[0]) / 255.0 * intensity, \
				ft_atof(tmp[1]) / 255.0 * intensity, \
				ft_atof(tmp[2]) / 255.0 * intensity);
		free(tmp);
		obj->radius = LIGHT_RADIUS;
	}
	else
		print_syntax_error(obj, "Light");
}
