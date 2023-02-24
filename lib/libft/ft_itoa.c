/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:39:00 by rbetz             #+#    #+#             */
/*   Updated: 2022/04/07 11:21:47 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int c)
{
	int	n;

	n = 0;
	if (c == 0)
		return (1);
	while (c != 0)
	{
		c = c / 10;
		n++;
	}
	return (n);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;
	int		vz;

	i = ft_count(n);
	vz = 0;
	if (n < 0)
		vz = 1;
	p = malloc(i + vz +1);
	if (p == NULL)
		return (NULL);
	p[i + vz] = '\0';
	if (vz == 1)
		p[0] = '-';
	while (i > 0)
	{
		if (vz == 1)
			p[i + vz - 1] = (n % 10) * -1 + '0';
		else
			p[i + vz - 1] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (p);
}
