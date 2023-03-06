/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:14:24 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/06 17:32:13 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#include <stdio.h>

int	xorshift_random(int seed)
{
	seed ^= seed >> 17;
	seed ^= seed << 5;
	seed ^= seed << 13;
	return (seed);
}

int	lcg_random(unsigned int seed)
{
	const unsigned int	a = (unsigned int)1664525;
	const unsigned int	c = (unsigned int)1013904227;

	return ((int)(a * seed + c));
}

int	xslcg_random(unsigned int seed)
{
	return (xorshift_random(seed) ^ lcg_random((unsigned int)&seed));
}

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
