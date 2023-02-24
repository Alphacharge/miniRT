/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:30:57 by rbetz             #+#    #+#             */
/*   Updated: 2022/07/18 15:57:07 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_str(char *h, char *n, size_t nl)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (h[i] != '\0')
	{
		if (h[i] == n[0])
		{
			while (j < nl && h[i + j] != '\0')
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

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	k;
	size_t	l;
	char	*hay;
	char	*nee;

	k = ft_strlen(needle);
	l = ft_strlen(haystack);
	hay = (char *)haystack;
	nee = (char *)needle;
	if (k > l)
		return (NULL);
	if (haystack == NULL || needle == NULL || l == 0 || k == 0)
		return (hay);
	return (find_str(hay, nee, k));
}
