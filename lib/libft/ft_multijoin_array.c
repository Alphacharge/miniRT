/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multijoin_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:08:04 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/22 10:58:28 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*copy_input(char **array, size_t len)
{
	char	*str;
	size_t	i;
	size_t	pos;

	str = ft_calloc(len + 1, sizeof(char));
	i = 0;
	pos = 0;
	while (str != NULL && array[i] != NULL)
	{
		len = ft_strlen(array[i]);
		ft_memcpy(&str[pos], array[i], len);
		pos += len;
		i++;
	}
	return (str);
}

static size_t	get_length(char **array)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (array[i] != NULL)
		len += ft_strlen(array[i++]);
	return (len);
}

/*Combines every string inside array into a single string. Array needs to be
terminated with NULL pointer.
Will not free any string inside the array, but frees the array.*/
char	*ft_multijoin_array(char **array)
{
	size_t	len;
	char	*str;

	if (array == NULL)
		return (NULL);
	len = get_length(array);
	str = copy_input(array, len);
	free(array);
	return (str);
}
