/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/27 13:50:59 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// static t_data	*init_data()
// {
// 	t_data	*data;

// 	data = malloc(sizeof(t_data));
// 	if (data == NULL)
// 		return (NULL);
// 	infile = ;
// 	items = NULL;
// 	return (data);
// }

static	mlx_t	*mlx_setup()
{
	mlx_t		*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (mlx == NULL)
		return (NULL);	//needs freeing
	return (mlx);
}

static mlx_image_t	*img_setup(mlx_t *mlx)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (img == NULL)
		return (NULL);	//needs freeing
	// ft_memset(data->img->pixels, 255, data->width * data->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img, 0, 0);
	return (img);
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_cam		*cam;
	t_map		*map;

	// data = init_data();
	map = parse_scene(argc, argv);
	ft_printf("------------------------\n");
	print_map(map);
	exit(0);
	mlx = mlx_setup();
	img = img_setup(mlx);
	cam = setup_camera(mlx->width, mlx->height);
	if (mlx == NULL || img == NULL || cam == NULL)
		return (EXIT_FAILURE);	//needs freeing
	draw_image(img, cam);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
