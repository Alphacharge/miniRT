/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:28:38 by fkernbac          #+#    #+#             */
/*   Updated: 2023/04/03 10:27:35 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	equal_vector(t_vec a, t_vec b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (true);
	return (false);
}

static t_vec	calc_corner(t_cam *cam)
{
	t_vec	corner;

	corner = new_vector(0, 0, 0);
	corner = factor_mult_vector(cam->horizontal, -0.5);
	corner = add_vector(corner, factor_mult_vector(cam->vertical, -0.5));
	corner = add_vector(corner, \
			factor_mult_vector(cam->direction, cam->focal_length));
	corner = subtract_vector(corner, cam->origin);
	return (corner);
}

t_cam	*setup_cam(t_obj **obj, int width, int height)
{
	t_cam	*cam;
	t_vec	down;
	int		i;

	i = 0;
	down = new_vector(0, 1, 0);
	cam = ft_calloc(1, sizeof(t_cam));
	if (cam == NULL)
		return (error_message(13), NULL);
	while (obj && obj[i] && obj[i]->type != CAM)
		i++;
	if (obj[i] == NULL)
		return (error_message(14), ft_free(cam), NULL);
	cam->origin = obj[i]->origin;
	cam->focal_length = width / (2 * tan(obj[i]->hei_fov / 2));
	cam->direction = unit_vector(obj[i]->vector);
	cam->horizontal = unit_vector(cross_vector(down, cam->direction));
	cam->horizontal = factor_mult_vector(cam->horizontal, width);
	cam->vertical = unit_vector(cross_vector(cam->direction, cam->horizontal));
	cam->vertical = factor_mult_vector(cam->vertical, height);
	cam->upper_left_corner = calc_corner(cam);
	cam->horizontal = unit_vector(cam->horizontal);
	cam->vertical = unit_vector(cam->vertical);
	return (cam);
}

bool	no_further_cam(t_obj *obj)
{
	while (obj != NULL)
	{
		if (obj && obj->type == CAM)
			return (false);
		obj++;
	}
	return (true);
}

void	get_next_cam(t_data *data)
{
	int	i;

	i = 0;
	while (data && data->obj && data->obj[i] && ((data->obj[i]->type != CAM) || (data->obj[i]->type == CAM && \
				!equal_vector(data->obj[i]->origin, data->cam->origin))))
		i++;
	while (data->obj[i] != NULL && ((data->obj[i]->type != CAM) || (data->obj[i]->type == CAM && \
				equal_vector(data->obj[i]->origin, data->cam->origin))))
		i++;
	if (data->obj[i] == NULL)
	{
		i = 0;
		while (data->obj[i] != NULL && ((data->obj[i]->type != CAM) || (data->obj[i]->type == CAM && \
				equal_vector(data->obj[i]->origin, data->cam->origin))))
			i++;
	}
	if (!no_further_cam(data->obj[i]))
	{
		ft_free(data->cam);
		data->cam = setup_cam(&data->obj[i], data->mlx->width, data->mlx->height);
	}
}
