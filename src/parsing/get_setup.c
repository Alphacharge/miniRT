/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:44:55 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/04 15:40:30 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_reso(t_obj *obj, char **split)
{
	if (obj && split && split[1] && split[2])
	{
		obj->type = RES;
		obj->rad_rat = ft_atof(split[1]);
		obj->hei_fov = ft_atof(split[2]);
	}
	else
		obj->type = -1;
}

void	get_cam(t_obj *obj, char **split)
{
	char **tmp;

	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = CAM;
		tmp = ft_split_p(split[1], ',');
		obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		tmp = ft_split_p(split[2], ',');
		obj->vector = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		obj->hei_fov = ft_atof(split[3]);
	}
	else
		obj->type = -1;
}

void	get_ambi(t_obj *obj, char **split)
{
	char **tmp;

	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = AMBI;
		obj->rad_rat = ft_atof(split[1]);
		tmp = ft_split_p(split[2], ',');
		obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
	}
	else
		obj->type = -1;
}

void	get_light(t_obj *obj, char **split)
{
	char **tmp;

	if (obj && split && split[1] && split[2] && split[3])
	{
		tmp = ft_split_p(split[1], ',');
		obj->type = LIGHT;
		obj->coord = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
		obj->rad_rat = ft_atof(split[2]);
		tmp = ft_split_p(split[3], ',');
		obj->color = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
	}
	else
		obj->type = -1;
}
