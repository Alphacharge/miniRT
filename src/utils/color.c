/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:32:39 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/27 17:02:51 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	float_to_color(float r, float g, float b)
{
	unsigned char	char_red;
	unsigned char	char_green;
	unsigned char	char_blue;

	char_red = 255 * r;
	char_green = 255 * g;
	char_blue = 255 * b;
	return (char_red << 24 | char_green << 16 | char_blue << 8 | 255);
}

int	factor_color(int rgba, float factor)
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
