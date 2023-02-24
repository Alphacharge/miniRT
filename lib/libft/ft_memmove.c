/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:34:37 by rbetz             #+#    #+#             */
/*   Updated: 2022/03/29 17:44:11 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_move(char *a, char *b, size_t v)
{
	size_t	i;

	i = 0;
	if (a < b)
	{
		while (i < v)
		{
			a[i] = b[i];
			i++;
		}
	}
	else
	{
		while (v > 0)
		{
			a[v -1] = b[v -1];
			v--;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*d;
	char			*s;

	d = (char *)dst;
	s = (char *)src;
	if (len > 0 && (dst != NULL || src != NULL))
	{
		ft_move(d, s, len);
	}
	return (dst);
}
