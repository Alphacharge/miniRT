/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:13:09 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/30 20:47:23 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_reso(t_obj *obj, char **split)
{
	if (obj && split && split[1] && split[2])
	{
		pre_check(obj, "Resolution Width", 3, split[1]);
		pre_check(obj, "Resolution Height", 3, split[2]);
		if (obj->type != -1)
			obj->type = RES;
		obj->radius = ft_atof(split[1]);
		obj->hei_fov = ft_atof(split[2]);
		obj->color = new_vector(0, 0, 0);
	}
	else
		print_syntax_error(obj, "Resolution");
}
