/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ambient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:12:44 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/28 15:53:58 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_ambi(t_obj *obj, char **split)
{
	char	**tmp;
	double	intensity;

	if (obj && split && split[1] && split[2])
	{
		pre_check(obj, "Ambientlight Ratio", 2, split[1]);
		pre_check(obj, "Ambientlight Color", 1, split[2]);
		if (obj->type != -1)
			obj->type = AMBI;
		intensity = ft_atof(split[1]);
		tmp = ft_split_p(split[2], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->color = new_vector(\
				ft_atof(tmp[0]) / 255.0 * intensity, \
				ft_atof(tmp[1]) / 255.0 * intensity, \
				ft_atof(tmp[2]) / 255.0 * intensity);
		free(tmp);
	}
	else
		print_syntax_error(obj, "Ambientlight");
}
