/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:51:46 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/30 14:13:10 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Combines all ambient lighting of the scene.*/
t_vec	*get_ambient_lighting(t_obj *obj)
{
	t_vec	ambient;
	t_vec	*allocate;

	while (obj != NULL)
	{
		if (obj->type == AMBI)
			ambient = add_vector(ambient, \
				factor_mult_vector(obj->color, obj->width));
		obj = obj->next;
	}
	allocate = ft_calloc(1, sizeof(t_vec));
	if (allocate == NULL)
		return (NULL);
	allocate->x = ambient.x;
	allocate->y = ambient.y;
	allocate->z = ambient.z;
	return (allocate);
}
