/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:33:29 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/31 11:05:14 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	is_no_rt_file(char *argv)
{
	int	len;

	if (argv == NULL)
		return (true);
	len = ft_strlen(argv);
	if (len < 3 || argv[len - 1] != 't' || \
		argv[len - 2] != 'r' || argv[len - 3] != '.')
		return (true);
	return (false);
}
