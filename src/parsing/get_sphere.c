/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:13:14 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/30 15:57:31 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_sphere(t_obj *obj, char **split)
{
	if (obj && split && split[1] && split[2] && split[3])
	{
		pre_check(obj, "Sphere Position", 1, split[1]);
		pre_check(obj, "Sphere Diameter", 2, split[2]);
		pre_check(obj, "Sphere Color", 1, split[3]);
		if (obj->type != -1)
			obj->type = SPHERE;
		obj->origin = insert_pos_vec(split[1], obj->type, POS);
		obj->radius = ft_atof(split[2]) / 2;
		obj->color = insert_color(split[3], obj->type);
		if (invalid_vector(obj->origin) || invalid_color(obj->color) || \
			obj->radius <= 0.0)
		{
			printf("Sphere Malloc Error\n");
			obj->type = -1;
		}
	}
	else
		print_syntax_error(obj, "Sphere");
}
