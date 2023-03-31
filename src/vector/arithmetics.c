/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:59:52 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/31 10:18:03 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Adds two vectors.*/
t_vec	add_vector(t_vec v1, t_vec v2)
{
	t_vec	vector;

	vector = new_vector(0, 0, 0);
	vector.x = v1.x + v2.x;
	vector.y = v1.y + v2.y;
	vector.z = v1.z + v2.z;
	return (vector);
}

/*Subtracts two vectors.
Returns vector pointing from v2 to v1.*/
t_vec	subtract_vector(t_vec v1, t_vec v2)
{
	t_vec	vector;

	vector = new_vector(0, 0, 0);
	vector.x = v1.x - v2.x;
	vector.y = v1.y - v2.y;
	vector.z = v1.z - v2.z;
	return (vector);
}

/*Multiplies coordinates of vectors.
Used mostly for color operations.*/
t_vec	multiply_vector(t_vec v1, t_vec v2)
{
	t_vec	vector;

	vector = new_vector(0, 0, 0);
	vector.x = v1.x * v2.x;
	vector.y = v1.y * v2.y;
	vector.z = v1.z * v2.z;
	return (vector);
}

/*Multiplies every vector coordinate with f.*/
t_vec	factor_mult_vector(t_vec v1, double f)
{
	t_vec	vector;

	vector = new_vector(0, 0, 0);
	vector.x = v1.x * f;
	vector.y = v1.y * f;
	vector.z = v1.z * f;
	return (vector);
}

/*Divides every vector coordinate by f. Checks for division by 0.*/
t_vec	factor_div_vector(t_vec v1, double f)
{
	t_vec	vector;

	if (f == 0.0)
		return (v1);
	vector = new_vector(0, 0, 0);
	vector.x = v1.x / f;
	vector.y = v1.y / f;
	vector.z = v1.z / f;
	return (vector);
}
