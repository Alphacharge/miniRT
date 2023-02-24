/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:38:56 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/31 10:53:50 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_counthex(unsigned long c)
{
	int	n;

	n = 0;
	if (c == 0)
		return (1);
	while (c != 0)
	{
		c = c / 16;
		n++;
	}
	return (n);
}

int	ft_hex(unsigned long quotient, char c)
{
	long	remainder;
	int		i;
	char	*result;

	if (quotient == 0)
		return (ft_putchar_fd_l('0', 1));
	i = ft_counthex(quotient);
	result = ft_calloc(i + 1, sizeof(char));
	if (result == NULL)
		return (0);
	while (quotient != 0 && i > 0)
	{
		i--;
		remainder = quotient % 16;
		if (remainder < 10)
			result[i] = remainder + '0';
		else if (c == 'X')
			result[i] = remainder + 'A' - 10;
		else
			result[i] = remainder + 'a' - 10;
		quotient = quotient / 16;
	}
	i = ft_putstr_fd_l(result, 1, c);
	free(result);
	return (i);
}

int	ft_flaghandling(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar_fd_l(va_arg(args, int), 1));
	else if (c == '%')
		return (ft_putchar_fd_l('%', 1));
	else if (c == 's')
		return (ft_putstr_fd_l(va_arg(args, char *), 1, c));
	else if (c == 'i' || c == 'd')
		return (ft_putstr_fd_l(ft_itoa(va_arg(args, long)), 1, c));
	else if (c == 'u')
		return (ft_putstr_fd_l(ft_ltoa(va_arg(args, unsigned int)), 1, c));
	else if (c == 'x' || c == 'X')
		return (ft_hex(va_arg(args, unsigned int), c));
	else if (c == 'p')
	{
		ft_putstr_fd_l("0x", 1, c);
		return (ft_hex(va_arg(args, unsigned long), c) + 2);
	}
	else
		return (0);
}

int	ft_loop_format(const char *format, int chars, va_list args)
{
	int	i;

	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			chars += ft_flaghandling(format[i + 1], args);
			i++;
		}
		else
			chars += ft_putchar_fd_l(format[i], 1);
		i++;
	}
	return (chars);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		chars;

	chars = 0;
	va_start(args, format);
	chars = ft_loop_format(format, chars, args);
	va_end(args);
	return (chars);
}
