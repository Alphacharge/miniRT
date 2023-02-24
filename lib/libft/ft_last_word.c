/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:28:23 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/22 11:06:50 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns a malloced string to last occurens of c in str from end*/
/*or if rev = 1 from start to the lim*/
char	*ft_last_word(const char *str, char c, int rev)
{
	int		i;
	int		len;
	char	*ret;

	len = ft_strlen(str);
	i = len;
	if (str == NULL)
		return (NULL);
	if (c == '\0')
		c = ' ';
	if (rev != 1)
		rev = 0;
	while (i >= 0 && str[i] != c)
		i--;
	if (rev == 0)
		ret = ft_calloc(len - i + 1, sizeof(char));
	else
		ret = ft_calloc(i, sizeof(char));
	if (rev == 0)
		ft_memcpy(ret, &str[i + 1], len - i);
	else
		ft_memcpy(ret, &str[0], i);
	return (ret);
}
