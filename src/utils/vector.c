/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:19:27 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/09 16:52:06 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*creates a new allocated vector*/
t_vec	*new_vector(double x, double y, double z)
{
	t_vec	*vector;

	vector = ft_calloc(1, sizeof(t_vec));
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
t_vec	factor_mult_vector(t_vec v1, double f)
{
	t_vec	vector;

	vector.x = v1.x * f;
	vector.y = v1.y * f;
	vector.z = v1.z * f;
	return (vector);
}

/*allocates a new vector with the result of vec1 / factor*/
t_vec	factor_div_vector(t_vec v1, double f)
{
	t_vec	vector;

	vector.x = v1.x / f;
	vector.y = v1.y / f;
	vector.z = v1.z / f;
	return (vector);
}

/*Scalar product of two vectors returns the angle between two vectors. A value
of 0 means they are orthogonal.*/
double	scalar_vector(t_vec v1, t_vec v2)
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

double	length_vector(t_vec v1)
{
	return (sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}

t_vec	unit_vector(t_vec v1)
{
	return (factor_div_vector(v1, length_vector(v1)));
}

t_vec	random_vector(unsigned int seed)
{
	t_vec	vector;

	vector.x = xorshift_random(seed) % 1000;
	vector.y = lcg_random(seed) % 1000 ;
	vector.z = xslcg_random(seed) % 1000;
	vector.x /= 1000;
	vector.y /= 1000;
	vector.z /= 1000;
	return (vector);
}

double	length_squared(t_vec vector)
{
	double	length;

	length = length_vector(vector);
	return (length * length);
}

/*For a better distribution of samples make this a unit vector.*/
t_vec	rand_in_unit_sphere(int seed)
{
	t_vec	rand_vec;

	while (1)
	{
		rand_vec = random_vector((unsigned int)seed);
		seed = xorshift_random(seed);
		if (length_squared(rand_vec) < 1)
			return (rand_vec);
	}
}

t_vec	rand_in_hemisphere(int seed, t_vec normal)
{
	t_vec	rand_vec;

	rand_vec = rand_in_unit_sphere(seed);
	if (scalar_vector(rand_vec, normal) > 0.0)
		return (rand_vec);
	else
		return (factor_mult_vector(rand_vec, -1));
}
