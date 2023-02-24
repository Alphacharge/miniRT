/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printflibft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:08:41 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/22 11:29:29 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd_l(char *s, int fd, char c)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
		{
			ft_putchar_fd_l(s[i], fd);
			i++;
		}
	}
	else
	{
		write(1, "(null)", 6);
		return (6);
	}
	if (c == 'i' || c == 'd' || c == 'u')
		free (s);
	return (i);
}

int	ft_putchar_fd_l(char c, int fd)
{
	write(fd, &c, sizeof(char));
	return (1);
}

// static int	ft_count(long c)
// {
// 	int	n;

// 	n = 0;
// 	if (c == 0)
// 		return (1);
// 	while (c != 0)
// 	{
// 		c = c / 10;
// 		n++;
// 	}
// 	return (n);
// }

// char	*ft_litoa(long n)
// {
// 	char	*p;
// 	int		i;
// 	int		vz;

// 	i = ft_count(n);
// 	vz = 0;
// 	if (n < 0)
// 		vz = 1;
// 	p = malloc(i + vz +1);
// 	if (p == NULL)
// 		return (NULL);
// 	p[i + vz] = '\0';
// 	if (vz == 1)
// 		p[0] = '-';
// 	while (i > 0)
// 	{
// 		if (vz == 1)
// 			p[i + vz - 1] = (n % 10) * -1 + '0';
// 		else
// 			p[i + vz - 1] = n % 10 + '0';
// 		n = n / 10;
// 		i--;
// 	}
// 	return (p);
// }
