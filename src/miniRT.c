/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/24 19:41:57 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_data	*init_data(t_data *data)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	// infile = ;
	// items = NULL;
	data->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (data->mlx == NULL)
		return (NULL);			//needs freeing
	data->img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	if (data->img == NULL)
		return (NULL);			//needs freeing
	// ft_memset(data->img->pixels, 255, data->width * data->height * sizeof(int32_t));
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = init_data(data);
	parse_scene(data, argc, argv);
	draw_image();
	// draw_grid(data);
	// print_keys();
	// mlx_key_hook(data->mlx, &keyhook, data);
	// mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
