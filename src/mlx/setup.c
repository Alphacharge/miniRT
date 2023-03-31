/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:47:34 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/31 10:44:36 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

mlx_image_t	*img_setup(mlx_t *mlx)
{
	mlx_image_t	*img;

	if (MLX == false)
		return (NULL);
	if (mlx == NULL)
		return (error_message(2), NULL);
	img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (img == NULL)
		return (error_message(12), NULL);
	ft_memset(img->pixels, 0, (mlx->width * mlx->height * sizeof(uint32_t)));
	mlx_image_to_window(mlx, img, 0, 0);
	return (img);
}

int	mlx_setup(t_obj *obj, t_data *data)
{
	mlx_t	*mlx;

	while (obj && obj->type != RES)
		obj = obj->next;
	data->width = WIDTH;
	data->height = HEIGHT;
	if (obj != NULL)
	{
		data->width = obj->radius;
		data->height = obj->hei_fov;
	}
	if (MLX == false)
		return (0);
	mlx = mlx_init((int32_t)data->width, (int32_t)data->height, \
		"miniRT", false);
	if (mlx == NULL)
		return (error_message(2), 1);
	mlx_set_window_pos(mlx, 10, 10);
	data->mlx = mlx;
	data->img = img_setup(mlx);
	if (data->img == NULL)
		return (mlx_terminate(mlx), 1);
	return (0);
}

void	run_mlx(t_data *data)
{
	if (MLX == false || data->mlx == NULL)
		return ;
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
}
