/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:47:02 by rbetz             #+#    #+#             */
/*   Updated: 2022/04/13 14:13:48 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;
	int	size;

	i = 0;
	if (lst == NULL)
		return (NULL);
	size = ft_lstsize(lst)-1;
	while (i < size)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
