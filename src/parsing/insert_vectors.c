/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:49:10 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/30 16:28:33 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//invalidate a vector to T_MAX
t_vec	invalid_vec(void)
{
	t_vec	new;

	new.x = T_MAX;
	new.y = T_MAX;
	new.z = T_MAX;
	return (new);
}

bool	invalid_vector(t_vec vec)
{
	if (vec.x == T_MAX && vec.y == T_MAX && vec.z == T_MAX)
		return (true);
	return (false);
}

t_vec	insert_color(char *bigfield, int type)
{
	char	**tmp;
	t_vec	new;

	tmp = ft_split_p(bigfield, ',');
	new = invalid_vec();
	if (tmp && tmp[0] && tmp[1] && tmp[2] && vector_check(COL, tmp, type))
	{
		new = new_vector(ft_atof(tmp[0]) / 255.0, \
			ft_atof(tmp[1]) / 255.0, \
			ft_atof(tmp[2]) / 255.0);
	}
	free(tmp);
	return (new);
}

t_vec	insert_pos_vec(char *bigfield, int type, char *key)
{
	char	**tmp;
	t_vec	new;

	tmp = ft_split_p(bigfield, ',');
	new = invalid_vec();
	if (tmp && tmp[0] && tmp[1] && tmp[2] && vector_check(key, tmp, type))
	{
		new = new_vector(ft_atof(tmp[0]), ft_atof(tmp[1]), \
		ft_atof(tmp[2]));
	}
	free(tmp);
	return (new);
}

bool	invalid_color(t_vec color)
{
	if (color.x > 1 || color.x < 0)
		return (true);
	if (color.y > 1 || color.y < 0)
		return (true);
	if (color.z > 1 || color.z < 0)
		return (true);
	return (false);
}
