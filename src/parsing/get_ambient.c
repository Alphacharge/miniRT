/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ambient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:12:44 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/07 11:23:32 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_ambi(t_obj *obj, char **split)
{
	char	**tmp;

	if (split[1] && !value_check(split[1]))
		printf("Ambientlight Ratio (%s) is not valid\n", split[1]);
	if (split[2] && !pre_field_check(split[2]))
		printf("Ambientlight Color (%s) Syntax Error\n", split[2]);
	if (obj && split && split[1] && split[2])
	{
		obj->type = AMBI;
		obj->rad_rat = ft_atof(split[1]);
		tmp = ft_split_p(split[2], ',');
		if (vector_check(COL, tmp, obj->type))
			obj->coord = new_vector(ft_atof(tmp[0]), \
				ft_atof(tmp[1]), ft_atof(tmp[2]));
		free(tmp);
	}
	else
		print_syntax_error(obj, "Ambientlight");
}