/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:22:45 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/28 16:37:03 by rbetz            ###   ########.fr       */
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
