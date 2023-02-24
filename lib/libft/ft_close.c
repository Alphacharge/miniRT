/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:11:55 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/22 11:30:36 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_close_and_neg(int *fd)
{
	close(*fd);
	*fd = FD_UNUSED;
}

void	ft_close_pipe_fds(int pipe[2])
{
	if (pipe[READ] != FD_UNUSED)
		ft_close_and_neg(&pipe[READ]);
	if (pipe[WRITE] != FD_UNUSED)
		ft_close_and_neg(&pipe[WRITE]);
}
