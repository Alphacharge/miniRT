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
	data->lines = 0;
	return (data);
}
static void	print_objs(t_obj **obj) {
	int	i;

	i = 0;
	while (obj && obj[i]) {
		printf("Object type: %d\n", obj[i]->type);
		i++;
	}
}

t_data	*parse(int argc, char **argv)
{
	t_data	*data;

	data = init_data();
	data->map = check_input(argc, argv);
	if (data->map == NULL)
		return (cleanup(data, 0), NULL);
	data->obj = ft_calloc(data->lines + 1, sizeof(t_obj*));
	if (data->obj == NULL)
		return (cleanup(data, 0), NULL);
	if (create_obj(data) < 0)
		return (cleanup(data, 0), NULL);
	print_objs(data->obj);
	printf("Parsing done.\n");
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = parse(argc, argv);
	if (data == NULL)
		return (EXIT_FAILURE);
	if (mlx_setup(data) != 0)
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
