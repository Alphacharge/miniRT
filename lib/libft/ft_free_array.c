/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:05:26 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/22 11:05:55 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Frees an array and every pointer inside.*/
void	*ft_free_array(void **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (NULL);
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i++] = NULL;
	}
	free(array);
	array = NULL;
	return (NULL);
}
