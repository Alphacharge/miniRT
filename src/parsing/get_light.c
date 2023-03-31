/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:13:00 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/31 08:10:28 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_light(t_obj *obj, char **split)
{
	if (obj && split && split[1] && split[2] && split[3])
	{
		pre_check(obj, "Light Position", 1, split[1]);
		pre_check(obj, "Light Ratio", 2, split[2]);
		pre_check(obj, "Light Color", 1, split[3]);
		if (obj->type != -1)
			obj->type = LIGHT;
		obj->origin = insert_pos_vec(split[1], obj->type, POS);
		obj->width = ft_atof(split[2]);
		obj->color = insert_color(split[3], obj->type);
		obj->radius = LIGHT_RADIUS;
		if (invalid_vector(obj->origin) || invalid_color(obj->color) || \
			obj->width > 1.0)
		{
			printf("Light Malloc Error or Ratio over 1\n");
			obj->type = -1;
		}
	}
	else
		print_syntax_error(obj, "Light");
}
