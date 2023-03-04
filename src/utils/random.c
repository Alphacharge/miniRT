/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:14:24 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/04 18:01:17 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	random_lcg(int seed)
{
	const unsigned int	a = (unsigned int)-563244923;
	const unsigned int	c = (unsigned int)-3364176919;
	const unsigned int	m = 259831419;
	unsigned int		random;

	random = (a * seed + c) % m;
	return (random);
}

unsigned	random_xorshift(unsigned int seed)
{
	unsigned	random;

	random = seed;
	random ^= random << 13;
	random ^= random >> 17;
	random ^= random << 5;
	return (random);
}

double	random_XSLCG(unsigned int seed)
{
	double			random;

	seed = seed % 100000000;
	random = random_xorshift(seed) ^ random_lcg(seed);
printf("random 1: %u ", (unsigned int) random);
	return (random);
}
