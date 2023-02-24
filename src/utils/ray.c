/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:42:25 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/24 18:52:14 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	*point_at(t_ray *ray, float t)
{
	t_vec	*product;
	t_vec	*point;

	product = factor_mult_vector(ray->direction, t);
	point = add_vector(ray->origin, product);
	ft_free(product);
	return (point);
}
