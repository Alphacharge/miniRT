/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:01:32 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/31 10:18:38 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Scalar product of two vectors returns the angle between two vectors.
A value of 0 means they are orthogonal.*/
double	scalar_vector(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*Cross product of two vectors returns normal vector. The absolute value
of this vector is also the surface area of the two vectors.*/
t_vec	cross_vector(t_vec v1, t_vec v2)
{
	t_vec	vector;

	vector = new_vector(0, 0, 0);
	vector.x = v1.y * v2.z - v1.z * v2.y;
	vector.y = v1.z * v2.x - v1.x * v2.z;
	vector.z = v1.x * v2.y - v1.y * v2.x;
	return (vector);
}
