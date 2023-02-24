/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:02:13 by rbetz             #+#    #+#             */
/*   Updated: 2022/04/06 17:10:43 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	ptr = malloc(ft_strlen(s1)+1 * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	return ((char *) ft_memcpy(ptr, s1, (size_t)ft_strlen(s1)+1));
}
