/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:59:11 by rbetz             #+#    #+#             */
/*   Updated: 2022/04/10 13:38:48 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	x;

	x = (char)c;
	len = ft_strlen(s);
	while ((len != 0) && (s[len] != x))
		len--;
	if ((len == 0) && (s[len] != x))
		return (0);
	else
		return ((char *)&s[len]);
}
