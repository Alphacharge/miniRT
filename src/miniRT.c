/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/21 13:03:25 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"




static t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		ft_error(NULL, 1);
	data->map = NULL;
	data->obj = NULL;
	data->mlx = NULL;
	data->img = NULL;
	data->cam = NULL;
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = init_data();
	data->map = check_input(argc, argv);
	if (data->map == NULL)
		return(cleanup(data, 0), EXIT_FAILURE);
	data->obj = create_obj(data->map);
	if (data->obj == NULL)
		return(cleanup(data, 0), EXIT_FAILURE);
	data->mlx = mlx_setup(data->obj, data);
	if (data->mlx == NULL)
		return(cleanup(data, 1), EXIT_FAILURE);
	data->img = img_setup(data->mlx);
	if (data->img == NULL)
		return(cleanup(data, 2), EXIT_FAILURE);
	if (data->mlx != NULL)
		data->cam = setup_cam(data->obj, data->img->width, data->img->height);
	else
		data->cam = setup_cam(data->obj, WIDTH, HEIGHT);
	if (data->cam == NULL)
		return(cleanup(data, 2), EXIT_FAILURE);
	//clean code until here
	if (create_threads(data))
		printf("Error Threads creating\n");
	run_mlx(data);
	if (remove_threads(data))
		printf("Error Threads joining\n");
	cleanup(data, 2);
	printf("Terminating.\n");
	return (EXIT_SUCCESS);
}
