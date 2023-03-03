/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:19:47 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/03 11:12:40 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// static char	*ft_calc(const char *s, int i, int j)
// {
// 	char	*p;

// 	p = ft_calloc(j + 1, 1);
// 	if (p == NULL)
// 		return (NULL);
// 	ft_memcpy(p, &s[i - j + 1], j);
// 	return (p);
// }

char	**ft_split_p(char *s, char c)
{
	char	**ptr;
	int		i;
	int		j;
	int		words;

	if (s == NULL)
		return (NULL);
	words = ft_wordcount(s, c);
	ptr = ft_calloc(words + 1, sizeof(char *));
	i = ft_strlen(s) - 1;
	while (i >= 0 && words > 0 && ptr != NULL)
	{
		if (s[i] != c)
		{
			j = 1;
			while (j <= i && s[i - j] != c)
				j++;
			ptr[--words] = &s[i - j];//ft_calc(s, i, j);
			if (ptr[words] == NULL)
				return (free(ptr), NULL);
			i = i - j + 1;
		}
		i--;
	}
	return (ptr);
}
