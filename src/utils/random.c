/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:14:24 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/27 20:33:13 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*This function expects a seed of about 1.000.000.000 length.*/
int	three_digits(unsigned int seed)
{
	unsigned int	random;
	unsigned int	sign;

	sign = (seed >> (sizeof(int) - 1) & 1);
	random = seed / 1000;
	random = random % 1000;
	if (sign == 1)
	random *= -1;
	return (random);
}

/*Returns a random value between 0 and 1.*/
double	random_double(unsigned int seed)
{
	double	random;

	random = xorshift_random(seed);
	seed = random;
	random = (double)random / (double)((double)INT_MAX + (double)1.0);
	if (random < 0)
		random *= -1;
	return (random);
}
