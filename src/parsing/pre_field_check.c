/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_field_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:01:08 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/07 10:59:55 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	value_check(char *line)
{
	int	m;
	int	d;

	m = 1;
	d = 1;
	if (line && *line == '-')
	{
		line++;
		m--;
	}
	while (line && *line)
	{
		if (d && *line == '.')
		{
			d--;
			line++;
		}
		if (*line != '\0' && (!ft_isdigit(*line) || (*line == '.' && !d)))
			return (0);
		if (*line != '\0')
			line++;
	}
	return (1);
}

int	vector_check(char *str, char **fields, int type)
{
	int	i;

	i = 0;
	while (fields && fields[i] && i < 3)
	{
		if (!value_check(fields[i]))
		{
			print_error(str, type, i, fields[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	pre_field_check(char *line)
{
	int	c;
	int	d;
	int	m;

	c = 0;
	d = 0;
	m = 0;
	while (line && *line)
	{
		if (*line == ',')
			c++;
		if (*line == '.')
			d++;
		if (*line == '-')
			m++;
		line++;
	}
	if (c != 2)
		return (0);
	if (d > 3)
		return (0);
	if (m > 3)
		return (0);
	return (1);
}
