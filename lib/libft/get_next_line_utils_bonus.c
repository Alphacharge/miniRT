/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:05:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/31 13:14:04 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_ns(char *s1, char *s2)
{
	char	*p1;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p1 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (p1 == NULL)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(p1, s1, (size_t)ft_strlen(s1));
	ft_memcpy(&p1[ft_strlen(s1)], s2, (size_t)ft_strlen(s2) + 1);
	free(s1);
	return (p1);
}
