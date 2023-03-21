/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:47:34 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/21 13:03:03 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

mlx_t	*mlx_setup(t_obj *obj, t_data *data)
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
	mlx = mlx_init((int32_t)data->width, (int32_t)data->height, \
		"miniRT", false);
	if (mlx == NULL)
		return (error_message(2), NULL);
	mlx_set_window_pos(mlx, 10, 10);
	return (mlx);
}

mlx_image_t	*img_setup(mlx_t *mlx)
{
	mlx_image_t	*img;

	if (mlx == NULL)
		return (error_message(2), NULL);
	img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (img == NULL)
		return (error_message(12), NULL);
	mlx_image_to_window(mlx, img, 0, 0);
	return (img);
}

void	run_mlx(t_data *data)
{
	if (data->mlx == NULL)
		return ;
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
