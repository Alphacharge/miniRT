/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:19:47 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/04 12:20:15 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* this split allocates a new **pointer and expect a allocated input string*/
/* it return pointer to the inputstring*/
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
			s[i + 1] = '\0';
			ptr[--words] = &s[i - j + 1];
			if (ptr[words] == NULL)
				return (free(ptr), NULL);
			i = i - j + 1;
		}
		i--;
	}
	return (ptr);
}
