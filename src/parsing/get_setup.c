/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:44:55 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/03 15:09:08 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_reso(t_obj *obj, char **split)
{
	if (obj && split && split[1] && split[2])
	{
		obj->type = RES;
		obj->dia_rat = ft_atof(split[1]);
		obj->hei_fov = ft_atof(split[2]);
	}
	else
		obj->type = -1;
}

void	get_cam(t_obj *obj, char **split)
{
	char **tmp;

	tmp = ft_split_p(split[1], ',');
	if (obj && split && split[1] && split[2] && split[3])
	{
		obj->type = CAM;
		obj->coord = new_vector(ft_atov(tmp[0]), ft_atov(tmp[1]), ft_atov(tmp[2]));
		free(tmp);
		tmp = ft_split_p(split[2], ',');
		obj->vector = new_vector(ft_atov(tmp[0]), ft_atov(tmp[1]), ft_atov(tmp[2]));
		free(tmp);
		obj->hei_fov = ft_atof(split[3]);
	}
	else
		obj->type = -1;
}

// void	get_ambi(t_obj *obj, char **split)
// {
	
// }

// void	get_light(t_obj *obj, char **split)
// {
	
// }
