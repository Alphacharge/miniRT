/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:03:29 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/25 18:10:16 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Returns same vector with value of 1.*/
t_vec	unit_vector(t_vec v1)
{
	return (factor_div_vector(v1, length_vector(v1)));
}

/*Returns a random vector [0;999].*/
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

/*Returns a random vector within a radius of 1.
For a better distribution of samples make this a unit vector.*/
t_vec	rand_in_unit_sphere(int seed)
{
	t_vec	rand_vec;

	while (1)
	{
		rand_vec = random_vector((unsigned int)seed);
		seed = xorshift_random(seed);
		if (length_squared(rand_vec) < 1)
			return (rand_vec);	//try returning unit vector instead?
		//return (unit_vector(rand_vec));
	}
}

/*Returns a random vector within a unit hemisphere.*/
t_vec	rand_in_hemisphere(int seed, t_vec normal)
{
	t_vec	rand_vec;

	rand_vec = rand_in_unit_sphere(seed);
	if (scalar_vector(rand_vec, normal) > 0.0)
		return (rand_vec);
	else
		return (factor_mult_vector(rand_vec, -1));
}
