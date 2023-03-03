/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:19:27 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/28 18:43:47 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*creates a new allocated vector*/
t_vec	*new_vector(float x, float y, float z)
{
	t_vec	*vector;

	vector = ft_calloc(1, sizeof(vector));
	if (vector == NULL)
		return (NULL);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

/*prints the vector values as XYZ*/
void	print_vector(t_vec vector)
{
	printf("(%f|%f|%f)", vector.x, vector.y, vector.z);
}

/*allocates a new vector with the result of vec1 + vec2*/
t_vec	add_vector(t_vec v1, t_vec v2)
{
	t_vec	vector;

	vector.x = v1.x + v2.x;
	vector.y = v1.y + v2.y;
	vector.z = v1.z + v2.z;
	return (vector);
}

/*allocates a new vector with the result of vec1 - vec2*/
t_vec	subtract_vector(t_vec v1, t_vec v2)
{
	t_vec	vector;

	vector.x = v1.x - v2.x;
	vector.y = v1.y - v2.y;
	vector.z = v1.z - v2.z;
	return (vector);
}

/*allocates a new vector with the result of vec1 * vec2*/
t_vec	multiply_vector(t_vec v1, t_vec v2)
{
	t_vec	vector;

	vector.x = v1.x * v2.x;
	vector.y = v1.y * v2.y;
	vector.z = v1.z * v2.z;
	return (vector);
}

/*allocates a new vector with the result of vec1 * factor*/
t_vec	factor_mult_vector(t_vec v1, float f)
{
	t_vec	vector;

	vector.x = v1.x * f;
	vector.y = v1.y * f;
	vector.z = v1.z * f;
	return (vector);
}

/*allocates a new vector with the result of vec1 / factor*/
t_vec	factor_div_vector(t_vec v1, float f)
{
	t_vec	vector;

	vector.x = v1.x / f;
	vector.y = v1.y / f;
	vector.z = v1.z / f;
	return (vector);
}

/*Scalar product of two vectors returns the angle between two vectors. A value
of 0 means they are orthogonal.*/
float	scalar_vector(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*Cross product of two vectors returns normal vector. The absolute value of this
vector is also the surface area of the two vectors.*/
t_vec	cross_vector(t_vec v1, t_vec v2)
{
	t_vec	vector;

	vector.x = v1.y * v2.z - v1.z * v2.y;
	vector.y = v1.z * v2.x - v1.x * v2.z;
	vector.z = v1.x * v2.y - v1.y * v2.x;
	return (vector);
}

float	length_vector(t_vec v1)
{
	return (sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}

t_vec	unit_vector(t_vec v1)
{
	return (factor_div_vector(v1, length_vector(v1)));
}
