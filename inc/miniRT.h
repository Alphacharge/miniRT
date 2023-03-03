/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:45:02 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/03 09:19:48 by rbetz            ###   ########.fr       */
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

# define WIDTH 800
# define HEIGHT 480
// # define WIDTH 1280
// # define HEIGHT 720
// # define WIDTH 1680
// # define HEIGHT 1050

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

typedef struct s_item
{
	char	*type;
	float	dia_rat;
	float	hei_fov;
	t_vec	coord;
	t_vec	vector;
	t_vec	color;
	struct s_item *next;
}				t_item;

typedef struct s_sphere
{
	t_vec	*center;
	float	radius;
}	t_sphere;

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
	t_vec	*upper_left_corner;
}	t_cam;

typedef struct s_map
{
	int		fd;
	char	**file;
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
t_map	*check_input(int argc, char **argv);
void	print_map(t_map *map);
int		ft_isvalue(int c);
int		ft_isspace(int c);
int		theend(char *s);
char	*kill_nltb(char *line);
int		first_iscomment(char *line);

//IMAGE
int	draw_image(mlx_image_t *img, t_cam *cam);

//ERROR
void	ft_error(t_data *data, int ecase);

//RAY UTILS
t_ray	*new_ray(t_vec *origin, t_vec *direction);
int		ray_color(t_ray *ray);
t_ray	*delete_ray(t_ray *ray);

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
t_cam	*delete_camera(t_cam *cam);

//COLOR UTILS
int	float_to_color(float r, float g, float b);
int	factor_color(int rgba, float factor);
int	add_color(int c1, int c2);

//UTILS
void	*ft_free(void *pointer);

#endif
