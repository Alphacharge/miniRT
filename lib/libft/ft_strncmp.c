/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:16:21 by rbetz             #+#    #+#             */
/*   Updated: 2022/03/29 17:21:42 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	d;
	unsigned char	s;

	i = 0;
	d = '\0';
	s = '\0';
	while (i < n)
	{
		d = s1[i];
		s = s2[i];
		if (d == '\0' || d != s)
			return (d - s);
		i++;
	}
	return (d - s);
}
