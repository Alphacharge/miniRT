/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:13:05 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/30 12:56:56 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_pln(t_obj *obj, char **split)
{
	if (obj && split && split[1] && split[2] && split[3])
	{
		pre_check(obj, "Plane Position", 1, split[1]);
		pre_check(obj, "Plane Vector", 1, split[2]);
		pre_check(obj, "Plane Color", 1, split[3]);
		if (obj->type != -1)
			obj->type = PLN;
		obj->origin = insert_pos_vec(split[1], obj->type, POS);
		obj->vector = insert_pos_vec(split[2], obj->type, ORI);
		obj->radius = ft_atof(split[2]);
		obj->color = insert_color(split[3], obj->type, 1);
		if (is_invalid(obj->origin) || is_invalid(obj->vector) \
			|| is_invalid(obj->color))
		{
			printf("Plane Malloc Error\n");
			obj->type = -1;
		}
	}
	else
		print_syntax_error(obj, "Plane");
}
//colors auf valid checken, koennen gerade ueber 255 sein
