/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:15:52 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/25 16:43:20 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*describes a valid value field for miniRT*/
int	ft_isvalue(int c)
{
	if ((c >= '0' && c <= '9') || c == '-' || c == ',' || c == '.')
		return (1);
	return (0);
}

/*identify any kind of space*/
int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\r' )
		return (1);
	if (c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

/*returns 1 if the rest of the string contains only spaces*/
int	theend(char *s)
{
	int	ret;

	ret = 1;
	while (s && *s != '\0' && ret)
	{
		ret = ft_isspace(*s);
		s++;
	}
	return (ret);
}

/*replace any kind of whitespace with spaces to split later*/
char	*kill_nltb(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] != '\0')
	{
		if (ft_isspace(line[i]))
			line[i] = ' ';
		i++;
	}
	return (line);
}

/*return 1 if the first char that isnt a space is a comment sign*/
int	first_iscomment(char *line)
{
	if (line == NULL)
		return (0);
	while (*line != '\0' && ft_isspace(*line))
		line ++;
	if (*line != '\0' && *line == '#')
		return (1);
	else
		return (0);
}
