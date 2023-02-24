/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_multiple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:04:24 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/22 11:18:24 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Frees memory of n arguments if they are not pointing to NULL.*/
void	ft_free_multiple(int n, ...)
{
	va_list	args;
	void	**pointer;

	pointer = NULL;
	if (n <= 0)
		return ;
	va_start(args, n);
	while (n > 0)
	{
		pointer = va_arg(args, void **);
		if (*pointer != NULL)
		{
			free(*pointer);
			*pointer = NULL;
		}
		n--;
	}
	va_end(args);
}
