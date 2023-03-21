/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:21:53 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/21 11:12:13 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	error_message(int ecase)
{
	if (ecase == 1)
		ft_putendl_fd("Error on allocating Datamemory!", 2);
	if (ecase == 2)
		ft_putendl_fd("Error on initialising MLX!", 2);
	if (ecase == 3)
		ft_putendl_fd("Error, too few Arguments!", 2);
	if (ecase == 4)
		ft_putendl_fd("Error, too much Arguments!", 2);
	if (ecase == 5)
		ft_putendl_fd("Error, empty Argument!", 2);
	if (ecase == 6)
		ft_putendl_fd("Error, can not open file.", 2);
	if (ecase == 7)
		ft_putendl_fd("Error on allocating Map!", 2);
	if (ecase == 8)
		ft_putendl_fd("Error on counting Lines!", 2);
	if (ecase == 9)
		ft_putendl_fd("Error on reading Lines!", 2);
	if (ecase == 10)
		ft_putendl_fd("Error on allocating Object!", 2);
	if (ecase == 11)
		ft_putendl_fd("Error on splitting Line!", 2);
	if (ecase == 12)
		ft_putendl_fd("Error on initialising MLX Image!", 2);
	if (ecase == 13)
		ft_putendl_fd("Error on allocating Object!", 2);
	if (ecase == 14)
		ft_putendl_fd("Error, there is no Cam in the Scene!", 2);
}

void	ft_error(t_data *data, int ecase)
{
	if (data != NULL)
		ft_free(data);
	error_message(ecase);
	// 6 // perror(filename);
	if (ecase == 2)
	{
		mlx_terminate(data->mlx);
		exit(EXIT_FAILURE);
	}
	exit (EXIT_SUCCESS);
}