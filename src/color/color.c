/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:32:39 by fkernbac          #+#    #+#             */
/*   Updated: 2023/03/27 15:00:09 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	double_to_color(double r, double g, double b)
{
	unsigned char	char_red;
	unsigned char	char_green;
	unsigned char	char_blue;

	char_red = 255 * r;
	char_green = 255 * g;
	char_blue = 255 * b;
	return (char_red << 24 | char_green << 16 | char_blue << 8 | 255);
}

int	factor_color(int rgba, double factor)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = ((rgba >> 24) & 0xFF) * factor;
	g = ((rgba >> 16) & 0xFF) * factor;
	b = ((rgba >> 8) & 0xFF) * factor;
	return (r << 24 | g << 16 | b << 8 | 255);
}

int	add_color(int c1, int c2)
{
	unsigned char	r;
	unsigned char	b;
	unsigned char	g;

	r = ((c1 >> 24) & 0xFF) + ((c2 >> 24) & 0xFF);
	g = ((c1 >> 16) & 0xFF) + ((c2 >> 16) & 0xFF);
	b = ((c1 >> 8) & 0xFF) + ((c2 >> 8) & 0xFF);
	return (r << 24 | g << 16 | b << 8 | 255);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
int get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
int get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
int	get_a(int rgba)
{
	return (rgba & 0xFF);
}

int	vector_to_color(t_vec color)
{
	return (get_rgba(color.x * 255, color.y * 255, color.z * 255, 255));
}

t_vec	color_to_vector(uint32_t rgba)
{
	t_vec	color;

	color.x = (double)get_r(rgba) / 255.0;
	color.y = (double)get_g(rgba) / 255.0;
	color.z = (double)get_b(rgba) / 255.0;
	return (color);
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
