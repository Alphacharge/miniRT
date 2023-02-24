/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:00:51 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/31 10:46:43 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns a malloced string to first occurens of c in str from beginning*/
/*or if rev = 1 from the end*/
char	*ft_first_word(const char *str, char c, int rev)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = ft_strlen(str);
	if (str == NULL)
		return (NULL);
	if (c == '\0')
		c = ' ';
	if (rev != 1)
		rev = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (rev == 0)
		ret = ft_calloc(i + 1, sizeof(char));
	else
		ret = ft_calloc(len - i + 1, sizeof(char));
	if (rev == 0)
		ft_memcpy(ret, &str[0], i);
	else
		ft_memcpy(ret, &str[i], len - i);
	return (ret);
}
