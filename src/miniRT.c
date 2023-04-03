/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2023/04/03 10:28:15 by rbetz            ###   ########.fr       */
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

t_data	*parse(int argc, char **argv)
{
	t_data	*data;

	data = init_data();
	data->map = check_input(argc, argv);
	if (data->map == NULL)
		return (cleanup(data, 0), NULL);
	data->obj = create_obj(data->map);
	if (data->obj == NULL)
		return (cleanup(data, 0), NULL);
	printf("Parsing done.\n");
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = parse(argc, argv);
	if (data == NULL)
		return (EXIT_FAILURE);
	if (mlx_setup(data->obj, data) != 0)
		return (cleanup(data, 1), EXIT_FAILURE);
	data->cam = setup_cam(data->obj, data->width, data->height);
	if (data->cam == NULL)
		return (cleanup(data, 2), EXIT_FAILURE);
	printf("Starting threads.\n");
	if (create_threads(data) != 0)
		return (cleanup(data, 3), EXIT_FAILURE);
	run_mlx(data);
	printf("Freeing memory.\n");
	escape(data);
	cleanup(data, 3);
	printf("Terminating...\n");
	return (EXIT_SUCCESS);
}
