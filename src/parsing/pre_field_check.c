/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_field_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:01:08 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/31 10:59:56 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//check the value for only one and leading -, only one . and digits
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

// is checking all 3 fields of a vector with value_check
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

//counts the amount of accepted chars and returns 0 if its to much.
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

void	pre_check(t_obj *obj, char *str, int type, char *tocheck)
{
	if (obj && tocheck == NULL)
	{
		obj->type = -1;
		return ;
	}
	if (tocheck && type == 1 && !pre_field_check(tocheck))
	{
		printf("%s (%s) Syntax Error\n", str, tocheck);
		obj->type = -1;
	}
	if (tocheck && type == 2 && !value_check(tocheck))
	{
		printf("%s (%s) is not valid\n", str, tocheck);
		obj->type = -1;
	}
	if (tocheck && type == 3 && !ft_strisdigit(tocheck))
	{
		printf("%s (%s) is not valid\n", str, tocheck);
		obj->type = -1;
	}
}
