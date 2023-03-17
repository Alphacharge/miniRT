/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/17 19:40:18 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


static	mlx_t	*mlx_setup(t_obj *obj)
{
	mlx_t	*mlx;

	while (obj && obj->type != RES)
		obj = obj->next;
	if (obj == NULL)
		mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	else
		mlx = mlx_init((int32_t)obj->radius, (int32_t)obj->hei_fov, "miniRT", true);
	if (mlx == NULL)
		return (NULL);	//needs freeing
	mlx_set_window_limit(mlx, 100, 100, 2000, 2000);
	mlx_set_window_pos(mlx, 0, 0);
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

static t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
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
//this leaks
	data->obj = create_obj(data->map);
printf("parsing done\n");
	if (MLX == true)
	{
		data->mlx = mlx_setup(data->obj);
		data->img = img_setup(data->mlx);
printf("mlx setup done\n");
		if (data->mlx == NULL || data->img == NULL)
			return (EXIT_FAILURE);	//needs freeing
	}
	data->cam = setup_camera(data->obj, WIDTH, HEIGHT);
printf("scene setup done\n");
	draw_image(data->img, data->cam, data->obj);
	if (MLX == 1)
	{
		mlx_key_hook(data->mlx, &my_keyhook, data);
		mlx_loop(data->mlx);
		mlx_terminate(data->mlx);
	}
	ft_free(data->cam);
	ft_free(data->map);
	ft_free(data);
	//free objs
	//free map->files?
	return (EXIT_SUCCESS);
}
