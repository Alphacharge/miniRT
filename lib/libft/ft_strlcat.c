/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:26:58 by rbetz             #+#    #+#             */
/*   Updated: 2022/03/31 16:35:36 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	sl;
	size_t	dl;
	size_t	i;
	size_t	j;

	sl = ft_strlen(src);
	dl = ft_strlen(dst);
	i = dl;
	j = 0;
	if (dl >= dstsize || src == NULL || dst == NULL)
		return (dstsize + sl);
	while (i < dstsize - 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (sl + dl);
}
