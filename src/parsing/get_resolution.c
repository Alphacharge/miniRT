/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:13:09 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/09 17:04:00 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_reso(t_obj *obj, char **split)
{
	if (split[1] && !ft_strisdigit(split[1]))
		printf("Resolution Width (%s) is not valid\n", split[1]);
	if (split[2] && !ft_strisdigit(split[2]))
		printf("Resolution Height (%s) is not valid\n", split[2]);
	if (obj && split && split[1] && split[2])
	{
		obj->type = RES;
		obj->radius = ft_atof(split[1]);
		obj->hei_fov = ft_atof(split[2]);
	}
	else
		print_syntax_error(obj, "Resolution");
}
