/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:53:25 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/30 14:37:46 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_negativ(char *nbr)
{
	while (nbr && *nbr && ft_isspace(*nbr))
		nbr++;
	if (*nbr == '-')
		return (1);
	return (0);
}

/*converts a string to a double*/
double	ft_atof(char *nbr)
{
	double	res;
	int		i;
	int		j;
	int		vz;

	j = 1;
	vz = 1;
	if (!nbr)
		return (0);
	res = ft_atoi(nbr);
	if (is_negativ(nbr))
		vz = -1;
	while (*nbr && *nbr != '.')
		nbr++;
	if (*nbr == '.')
		nbr++;
	i = ft_strlen(nbr);
	while (i-- > 0)
		j *= 10;
	res += (double)ft_atoi(nbr) * vz / j;
	return (res);
}
