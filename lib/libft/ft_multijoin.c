/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multijoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:08:04 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/22 10:57:21 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*copy_input(bool tofr, int n, char **input)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (i < n)
		len += ft_strlen(input[i++]);
	str = ft_calloc(len + 1, sizeof(char));
	i = 0;
	len = 0;
	while (str != NULL && i < n)
	{
		ft_memcpy(&str[len], input[i], ft_strlen(input[i]));
		len += ft_strlen(input[i]);
		if (tofr == true)
		{
			free(input[i]);
			input[i] = NULL;
		}
		i++;
	}
	return (str);
}

static char	**read_input(int n, va_list args)
{
	int		i;
	char	**input;

	i = 0;
	input = ft_calloc(n + 1, sizeof(char *));
	input[n] = NULL;
	while (i < n)
	{
		input[i] = va_arg(args, char *);
		i++;
	}
	return (input);
}

/*tofr, frees the input if true, n is the amount of strings,*/
/*accepts endless strings to join together*/
char	*ft_multijoin(bool tofr, int n, ...)
{
	va_list	args;
	char	**input;
	char	*str;

	if (n < 2)
		return (NULL);
	va_start(args, n);
	input = read_input(n, args);
	str = copy_input(tofr, n, input);
	va_end(args);
	free(input);
	input = NULL;
	return (str);
}
