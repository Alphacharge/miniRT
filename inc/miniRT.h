/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:45:02 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/27 14:03:40 by rbetz            ###   ########.fr       */
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

# define WIDTH 50
# define HEIGHT 30

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vec;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

// typedef enum e_type
// {
// 	CAM,
// 	LIGHT,
// 	AMBI,
// 	SPHERE,
// 	CYL,
// 	RECT,
// 	PLN
// }	t_type;

// typedef struct s_item
// {
// 	int		type;
// 	double	ratio;
// 	double	x;
// 	double	y;
// 	double	z;
// 	int		red;
// 	int		green;
// 	int		blue;
// 	struct s_item next;
// }				t_item;

typedef struct s_ray
{
	t_vec	*origin;
	t_vec	*direction;
}		t_ray;

typedef struct s_camera
{
	float	focal_length;
	t_vec	*origin;
	t_vec	*horizontal;
	t_vec	*vertical;
	t_vec	*lower_left_corner;
}	t_cam;

typedef struct s_map
{
	int		fd;
	char	**lines;
	char	***file;
	int		error;
	int		size;
}	t_map;

typedef struct s_data
{
	mlx_t					*mlx;
	mlx_image_t				*img;
	// int						height;
	// int						width;
	// int						infile;
	// typedef struct s_item	*items;
}							t_data;

//PARSING
t_map	*parse_scene(int argc, char **argv);
void	print_map(t_map *map);
int		realloc_map(t_map *map);
//IMAGE
int	draw_image(mlx_image_t *img, t_cam *cam);

//ERROR
void	ft_error(t_data *data, int ecase);

//RAY UTILS
t_ray	*new_ray(t_vec *origin, t_vec *direction);
int		ray_color(t_ray *ray);

//VECTOR UTILS
t_vec	*new_vector(float x, float y, float z);
void	print_vector(t_vec *vector);
t_vec	*add_vector(t_vec *v1, t_vec *v2);
t_vec	*subtract_vector(t_vec *v1, t_vec *v2);
t_vec	*multiply_vector(t_vec *v1, t_vec *v2);
t_vec	*factor_mult_vector(t_vec *v1, float f);
t_vec	*factor_div_vector(t_vec *v1, float f);
float	scalar_vector(t_vec *v1, t_vec *v2);
t_vec	*cross_vector(t_vec *v1, t_vec *v2);
float	length_vector(t_vec *v1);
t_vec	*unit_vector(t_vec *v1);

//CAMERA
t_cam	*setup_camera(int width, int height);

//COLOR UTILS
int	float_to_color(float r, float g, float b);
int	multiply_color(int rgba, int factor);
int	add_color(int c1, int c2);

//UTILS
void	*ft_free(void *pointer);

#endif
