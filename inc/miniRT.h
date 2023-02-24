/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:45:02 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/24 19:25:06 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>		//printf
# include <fcntl.h>		//open
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "MLX42.h"
# include "libft.h"

# define WIDTH 860
# define HEIGHT 640

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vec;


typedef enum e_type
{
	CAM,
	LIGHT,
	AMBI,
	SPHERE,
	CYL,
	RECT,
	PLN
}	t_type;

typedef struct s_item
{
	int		type;
	double	ratio;
	double	x;
	double	y;
	double	z;
	int		red;
	int		green;
	int		blue;
	struct s_item next;
}				t_item;

typedef struct s_ray
{
	t_vec	*origin;
	t_vec	*direction;
}		t_ray;

typedef struct s_camera
{

}	t_cam;


typedef struct s_data
{
	mlx_t					*mlx;
	mlx_image_t				*img;
	int						height;
	int						width;
	int						infile;
	typedef struct s_item	*items;
}							t_data;

void	ft_error(t_data *data, int ecase);

//VECTOR UTILS
t_vec	*new_vector(float x, float y, float z);
void	print_vector(t_vec *vector);
t_vec	*add_vector(t_vec *v1, t_vec *v2);
t_vec	*subtract_vector(t_vec *v1, t_vec *v2);
t_vec	*multiply_vector(t_vec *v1, t_vec *v2);
t_vec	*factor_mult_vector(t_vec *v1, float f);
t_vec	*factor_div_vector(t_vec *v1, float f);
float	scalar_vector(t_vec *v1, t_vec *v2);
float	cross_vector(t_vec *v1, t_vec *v2);
float	length_vector(t_vec *v1);
t_vec	*unit_vector(t_vec *v1);

#endif
