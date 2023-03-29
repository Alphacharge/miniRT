/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ambient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:12:44 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/28 17:32:53 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_ambi(t_obj *obj, char **split)
{
	double	intens;

	if (obj && split && split[1] && split[2])
	{
		pre_check(obj, "Ambientlight Ratio", 2, split[1]);
		pre_check(obj, "Ambientlight Color", 1, split[2]);
		if (obj->type != -1)
			obj->type = AMBI;
		intens = ft_atof(split[1]);
		obj->color = insert_color(split[2], obj->type, intens);
		if (is_invalid(obj->color))
		{
			printf("Ambientlight Malloc Error\n");
			obj->type = -1;
		}
	}
	else
		print_syntax_error(obj, "Ambientlight");
}
