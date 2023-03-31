/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:32:39 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/31 13:06:30 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	vector_to_color(t_vec color)
{
	return (get_rgba(color.x * 255, color.y * 255, color.z * 255, 255));
}

int	gamma_correction(t_vec color)
{
	const double	gamma = 2.2;

	color.x = pow(color.x, 1 / gamma);
	color.y = pow(color.y, 1 / gamma);
	color.z = pow(color.z, 1 / gamma);
	return (vector_to_color(color));
}

t_vec	color_clamp(t_vec color)
{
	if (color.x > 1)
		color.x = 1;
	else if (color.x < 0)
		color.x = 0;
	if (color.y > 1)
		color.y = 1;
	else if (color.y < 0)
		color.y = 0;
	if (color.z > 1)
		color.z = 1;
	else if (color.z < 0)
		color.z = 0;
	return (color);
}

t_vec	abs_vector(t_vec color)
{
	color.x = fabs(color.x);
	color.y = fabs(color.y);
	color.z = fabs(color.z);
	return (color);
}
