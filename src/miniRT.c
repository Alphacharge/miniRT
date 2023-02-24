/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/24 15:39:51 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static	init_data(data)
{
	mlx = NULL;
	img = NULL;
	width = 860;
	height = 640;
	infile = ;
	items = NULL;
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		ft_error(data, 1);
	init_data(data);
	parse_scene(data, argc, argv);
	data->mlx = mlx_init(data->width, data->height, "miniRT", false);
	if (data->mlx == NULL)
		ft_error(data, 2);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	ft_memset(data->img->pixels, 255, data->width * data->height * sizeof(int32_t));
	// draw_grid(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	// print_keys();
	// mlx_key_hook(data->mlx, &keyhook, data);
	// mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	ft_error(data, 0);
	return (0);
}
