/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:32:03 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/31 12:11:14 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strreplace(char *str, char *tofind, char *replace)
{
	char	*tempstring;
	char	*searchstart;
	int		len;

	len = 0;
	searchstart = ft_strstr(str, tofind);
	tempstring = ft_strdup(str);
	len = ft_strlen(str) - ft_strlen(searchstart);
	str[len] = '\0';
	ft_strlcat(str, replace, ft_strlen(str) + ft_strlen(replace) + 1);
	len += ft_strlen(tofind);
	ft_strlcat(str, &tempstring[len], ft_strlen(tempstring) \
		- ft_strlen(tofind) + ft_strlen(replace) + 1);
	free(tempstring);
}
