/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtx_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:00:00 by rbetz             #+#    #+#             */
/*   Updated: 2026/05/13 10:00:00 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "rtx.h"

static int	count_objects(t_obj *obj)
{
	int	count;

	count = 0;
	while (obj != NULL)
	{
		count++;
		obj = obj->next;
	}
	return (count);
}

static void	convert_one_obj(t_gpu_obj *gpu, t_obj *obj)
{
	gpu->type = obj->type;
	gpu->radius = obj->radius;
	gpu->width = obj->width;
	gpu->hei_fov = obj->hei_fov;
	gpu->origin[0] = obj->origin.x;
	gpu->origin[1] = obj->origin.y;
	gpu->origin[2] = obj->origin.z;
	gpu->vector[0] = obj->vector.x;
	gpu->vector[1] = obj->vector.y;
	gpu->vector[2] = obj->vector.z;
	gpu->vector2[0] = obj->vector2.x;
	gpu->vector2[1] = obj->vector2.y;
	gpu->vector2[2] = obj->vector2.z;
	gpu->color[0] = obj->color.x;
	gpu->color[1] = obj->color.y;
	gpu->color[2] = obj->color.z;
}

t_gpu_obj	*convert_objects(t_obj *obj, int *num_objects)
{
	t_gpu_obj	*gpu_objs;
	int			count;
	int			i;

	count = count_objects(obj);
	*num_objects = count;
	gpu_objs = (t_gpu_obj *)malloc(sizeof(t_gpu_obj) * count);
	if (gpu_objs == NULL)
		return (NULL);
	i = 0;
	while (obj != NULL)
	{
		convert_one_obj(&gpu_objs[i], obj);
		obj = obj->next;
		i++;
	}
	return (gpu_objs);
}

void	convert_camera(t_gpu_cam *gpu_cam, t_cam *cam)
{
	gpu_cam->focal_length = cam->focal_length;
	gpu_cam->origin[0] = cam->origin.x;
	gpu_cam->origin[1] = cam->origin.y;
	gpu_cam->origin[2] = cam->origin.z;
	gpu_cam->direction[0] = cam->direction.x;
	gpu_cam->direction[1] = cam->direction.y;
	gpu_cam->direction[2] = cam->direction.z;
	gpu_cam->horizontal[0] = cam->horizontal.x;
	gpu_cam->horizontal[1] = cam->horizontal.y;
	gpu_cam->horizontal[2] = cam->horizontal.z;
	gpu_cam->vertical[0] = cam->vertical.x;
	gpu_cam->vertical[1] = cam->vertical.y;
	gpu_cam->vertical[2] = cam->vertical.z;
	gpu_cam->upper_left_corner[0] = cam->upper_left_corner.x;
	gpu_cam->upper_left_corner[1] = cam->upper_left_corner.y;
	gpu_cam->upper_left_corner[2] = cam->upper_left_corner.z;
}

void	convert_config(t_gpu_config *cfg, t_data *data)
{
	t_obj	*obj;
	t_vec	ambient;

	cfg->width = data->width;
	cfg->height = data->height;
	cfg->max_depth = MAX_DEPTH;
	cfg->soft_shadow = SOFT_SHADOW;
	cfg->bounces = BOUNCES;
	cfg->sky = SKY;
	cfg->albedo = ALBEDO;
	cfg->light_factor = LIGHT_FACTOR;
	ambient.x = 0;
	ambient.y = 0;
	ambient.z = 0;
	obj = data->obj;
	while (obj != NULL)
	{
		if (obj->type == AMBI)
		{
			ambient.x += obj->color.x * obj->width;
			ambient.y += obj->color.y * obj->width;
			ambient.z += obj->color.z * obj->width;
		}
		obj = obj->next;
	}
	cfg->ambient[0] = ambient.x;
	cfg->ambient[1] = ambient.y;
	cfg->ambient[2] = ambient.z;
}
