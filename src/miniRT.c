/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/24 10:05:23 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_data(t_data *data)
{
	// data->map = NULL;
	// data->var = malloc(sizeof(t_var));
	// if (data->var == NULL)
	// 	ft_error(data, 5);
	// init_var(data);
	data->fx = 0;
	data->fy = 0;
	data->tx = 0;
	data->ty = 0;
	data->fc = malloc(4 * sizeof(int));
	data->llen = 30;
	data->llen1 = 0;
	data->llen2 = 0;
	data->zoom = 1;
	data->angx = M_PI / 6;
	data->angy = M_PI / 6;
	data->angz = 0;
	data->stefa = 5;
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	// if (data == NULL)
	// 	ft_error(data, 3);
	init_data(data);
	// parse_map(data, argc, argv);
	data->mlx = mlx_init(860, 640, "miniRT", false);
	// if (data->mlx == NULL)
	// 	ft_error(data, 7);
	data->img = mlx_new_image(data->mlx, 860, 640);
	ft_memset(data->img->pixels, 255, 860 * 640 * sizeof(int32_t));
	// draw_grid(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	// print_keys();
	// mlx_key_hook(data->mlx, &keyhook, data);
	// mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	// ft_error(data, 0);
	(void) argc;
	(void) argv;
	return (0);
}
