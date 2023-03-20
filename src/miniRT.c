/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/20 19:52:28 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


static	mlx_t	*mlx_setup(t_obj *obj, t_data *data)
{
	mlx_t	*mlx;

	while (obj && obj->type != RES)
		obj = obj->next;
	if (obj == NULL)
	{
		data->width = obj->radius;
		data->height = obj->hei_fov;
	}
	else
	{
		data->width = WIDTH;
		data->height = HEIGHT;
	}
	mlx = mlx_init((int32_t)data->width, (int32_t)data->height, "miniRT", false);
	if (mlx == NULL)
		return (NULL);
	// mlx_set_window_limit(mlx, 100, 100, 2000, 2000);
	mlx_set_window_pos(mlx, 10, 10);
	return (mlx);
}

static mlx_image_t	*img_setup(mlx_t *mlx)
{
	mlx_image_t	*img;

	if (mlx == NULL)
		return (NULL);
	img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (img == NULL)
		return (NULL);
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

static void	run_mlx(t_data *data)
{
	if (data->mlx == NULL)
		return ;
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}

void	cleanup(t_data *data)
{
	ft_free(data->cam);
	ft_free(data->map);
	ft_free(data);
	//free objs
	//free map->files?
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = init_data();
	data->map = check_input(argc, argv);
	data->obj = create_obj(data->map);
	data->mlx = mlx_setup(data->obj, data);
	data->img = img_setup(data->mlx);
	if (data->mlx != NULL)
		data->cam = setup_camera(data->obj, data->img->width, data->img->height);
	else
		data->cam = setup_camera(data->obj, WIDTH, HEIGHT);
	if (create_threads(data))
		printf("Error Threads creating\n");
	run_mlx(data);
	if (remove_threads(data))
		printf("Error Threads joining\n");
	cleanup(data);
	printf("Terminating.\n");
	return (EXIT_SUCCESS);
}
