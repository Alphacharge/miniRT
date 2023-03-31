/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:19:27 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/31 10:19:22 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Returns vector allocated on stack.*/
t_vec	new_vector(double x, double y, double z)
{
	t_vec	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

/*Multiplies every coordinate with -1.*/
t_vec	invert_vector(t_vec vec)
{
	t_vec	v;

	v = new_vector(0, 0, 0);
	v.x = -vec.x;
	v.y = -vec.y;
	v.z = -vec.z;
	return (v);
}

/*Returns length of vector.*/
double	length_vector(t_vec v1)
{
	return (sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}

/*Returns length squared of vector. Saves from calculating the length twice.*/
double	length_squared(t_vec vector)
{
	double	length;

	length = length_vector(vector);
	return (length * length);
}

/*prints the vector values as XYZ*/
void	print_vector(t_vec vector)
{
	printf("(%f|%f|%f)", vector.x, vector.y, vector.z);
}
