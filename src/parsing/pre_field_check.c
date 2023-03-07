/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_field_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:01:08 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/06 18:23:17 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_strisdigit(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}


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
static char **def_color(void)
{
	static char *color[3];
	
	color[0] = "Red";
	color[1] = "Green";
	color[2] = "Blue";
	return (color);
}
void print_error(char *str, int type, int i, char *field)
{
	char **color;

	color = def_color();
	if (type == CAM)
		printf("Camera %s %c (%s) is not valid\n", str, i + 88, field);
	if (type == AMBI)
		printf("Ambientlight %s %s (%s) is not valid\n", str, color[i], field);
	if (type == LIGHT && ft_strcmp(str, POS))
		printf("Light %s %c (%s) is not valid\n", str, i + 88, field);
	else if (type == LIGHT && ft_strcmp(str, COL))
		printf("Light %s %s (%s) is not valid\n", str, color[i], field);
	if (type == SPHERE && ft_strcmp(str, POS))
		printf("Light %s %c (%s) is not valid\n", str, i + 88, field);
	else if (type == SPHERE && ft_strcmp(str, COL))
		printf("Light %s %s (%s) is not valid\n", str, color[i], field);
	if (type == PLN && ft_strcmp(str, POS))
		printf("Plane %s %d (%s) is not valid\n", str, i + 88, field);
	else if (type == PLN && ft_strcmp(str, ORI))
		printf("Plane %s %d (%s) is not valid\n", str, i + 88, field);
	else if (type == PLN && ft_strcmp(str, COL))
		printf("Plane %s %s (%s) is not valid\n", str, color[i], field);
	//maybe one else can be removed
	if (type == CYL && ft_strcmp(str, POS))
		printf("Cylinder %s %c (%s) is not valid\n", str, i + 88, field);
	else if (type == CYL && ft_strcmp(str, ORI))
		printf("Cylinder %s %d (%s) is not valid\n", str, i + 88, field);
	else if (type == CYL && ft_strcmp(str, COL))
		printf("Cylinder %s %s (%s) is not valid\n", str, color[i], field);
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