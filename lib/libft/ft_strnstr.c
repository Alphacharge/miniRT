/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:35:49 by rbetz             #+#    #+#             */
/*   Updated: 2022/03/31 17:43:24 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_it(char *h, char *n, size_t nl, size_t sl)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (h[i] != '\0' && i < sl)
	{
		if (h[i] == n[0])
		{
			while (j < nl && i + j < sl)
			{
				if (h[i + j] == n[j])
					j++;
				else
				{
					j = 0;
					break ;
				}
			}
			if (j == nl)
				return ((char *)&h[i]);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	k;
	size_t	l;
	char	*hay;
	char	*nee;

	k = ft_strlen(needle);
	l = ft_strlen(haystack);
	hay = (char *)haystack;
	nee = (char *)needle;
	if (k > l || k > len)
		return (NULL);
	if (haystack == NULL || needle == NULL || len < 1 || l == 0 || k == 0)
		return (hay);
	return (find_it(hay, nee, k, len));
}
