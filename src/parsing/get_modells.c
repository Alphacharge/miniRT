/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_modells.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:50 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/03 17:44:37 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_sphere(t_obj *obj, char **split)
{
	char **tmp;

	tmp = ft_split_p(split[1], ',');
	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = SPHERE;
		obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		obj->rad_rat = ft_atof(split[2]) / 2;
		tmp = ft_split_p(split[3], ',');
		obj->color = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
	}
	else
		obj->type = -1;
}

// void	get_pln(t_obj *obj, char **split)
// {

// }

// void	get_cyl(t_obj *obj, char **split)
// {

// }

// void	get_rect(t_obj *obj, char **split)
// {

// }
