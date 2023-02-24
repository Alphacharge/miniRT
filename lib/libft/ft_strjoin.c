/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:31:29 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/31 13:14:02 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p1;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p1 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (p1 == NULL)
		return (NULL);
	ft_memcpy(p1, s1, (size_t)ft_strlen(s1));
	ft_memcpy(&p1[ft_strlen(s1)], s2, (size_t)ft_strlen(s2) + 1);
	return (p1);
}
