/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:02:20 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/25 17:03:34 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	*ft_free(void *pointer)
{
	if (pointer != NULL)
		free(pointer);
	pointer = NULL;
	return (pointer);
}
