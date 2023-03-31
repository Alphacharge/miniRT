/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:10:57 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/31 10:14:24 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Returns coordinates of a point on ray.*/
t_vec	point_at(t_ray ray, double t)
{
	t_vec	product;
	t_vec	target;

	product = new_vector(0, 0, 0);
	target = new_vector(0, 0, 0);
	product = factor_mult_vector(ray.direction, t);
	target = add_vector(ray.origin, product);
	return (target);
}
