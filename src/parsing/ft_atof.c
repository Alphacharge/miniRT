/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:53:25 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/03 14:14:46 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	ft_atof(char *nbr)
{
	double res;
	int i;
	int j;

	j = 1;
	if (!nbr)
		return (0);
	res = ft_atoi(nbr);
	while (*nbr && *nbr != '.')
		nbr++;
	if (*nbr == '.')
		nbr++;
	i = ft_strlen(nbr);
	while (i-- > 0)
		j *= 10;
	res += (double)ft_atoi(nbr) / j;
	return (res);
}
