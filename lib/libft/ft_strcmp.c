/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:19:41 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/22 11:07:17 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*returns the differece of s1 and s2, -1 if a string is NULL*/
/*returns 0 if there is no difference*/
int	ft_strcmp(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	if (len1 != len2)
		return (len1 - len2);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0')
		return (0);
	else
		return (s1[i] - s2[i]);
}
