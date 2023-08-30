/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:13:05 by rbetz             #+#    #+#             */
/*   Updated: 2023/08/30 15:33:02 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_pln(t_obj *obj, char **split)
{
	if (obj && split && split[1] && split[2] && split[3] && split[4])
	{
		pre_check(obj, "Plane Position", 1, split[1]);
		pre_check(obj, "Plane Vector", 1, split[2]);
		pre_check(obj, "Plane Color", 1, split[3]);
		pre_check(obj, "Plane Reflection", 2, split[4]);
		if (obj->type != -1)
			obj->type = PLN;
		obj->origin = insert_pos_vec(split[1], obj->type, POS);
		obj->vector = unit_vector(insert_pos_vec(split[2], obj->type, ORI));
		obj->radius = ft_atof(split[2]);
		obj->color = insert_color(split[3], obj->type);
		obj->reflection = ft_atof(split[4]);
		if (invalid_vector(obj->origin) || invalid_vector(obj->vector) \
			|| invalid_color(obj->color) || obj->reflection < 0.0 \
			|| obj->reflection > 1.0)
		{
			printf("Plane Error\n");
			obj->type = -1;
		}
	}
	else
		print_syntax_error(obj, "Plane");
}
//colors auf valid checken, koennen gerade ueber 255 sein
