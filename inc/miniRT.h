/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:45:02 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/09 17:38:12 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>		//printf
# include <fcntl.h>		//open
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include "MLX42.h"
# include "libft.h"

# define WIDTH 800
# define HEIGHT 480
// # define WIDTH 1280
// # define HEIGHT 720
// # define WIDTH 1680
// # define HEIGHT 1050

# define MAX_DEPTH 50

# define T_MIN 0.001
# define T_MAX __DBL_MAX__

# define LIGHT_RADIUS 100

# define COL "Color"
# define POS "Position"
# define ORI "Orientation"

typedef enum e_type
{
	CAM,
	LIGHT,
	AMBI,
	SPHERE,
	CYL,
	PLN,
	RES
}	t_type;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}			t_color;

typedef struct s_obj
{
	int		type;
	double	radius;
	double	intensity;
	double	hei_fov;
	t_vec	*coord;
	t_vec	*vector;
	t_vec	*color;
	struct s_obj *next;
}			t_obj;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
	double	closest_t;
	t_obj	*closest_object;
	t_vec	normal;
}			t_ray;

typedef struct s_camera
{
	double	focal_length;
	t_vec	origin;
	t_vec	direction;
	t_vec	horizontal;
	t_vec	vertical;
	t_vec	upper_left_corner;
}			t_cam;

typedef struct s_map
{
	int		fd;
	char	**file;
}	t_map;

typedef struct s_data
{
	mlx_t					*mlx;
	mlx_image_t				*img;
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
t_obj	*create_obj(t_map *map);
char	**ft_split_p(char *s, char c);
void	get_reso(t_obj *obj, char **split);
void	get_cam(t_obj *obj, char **split);
void	get_ambi(t_obj *obj, char **split);
void	get_light(t_obj *obj, char **split);
void	get_sphere(t_obj *obj, char **split);
void	get_pln(t_obj *obj, char **split);
void	get_cyl(t_obj *obj, char **split);
double	ft_atof(char *nbr);
int		pre_field_check(char *line);
int		value_check(char *line);
int		ft_strisdigit(char *str);
int		vector_check(char *str, char **fields, int type);
void	print_error(char *str, int type, int i, char *field);
char	**def_color(void);
void	print_syntax_error(t_obj *obj, char *str);

//IMAGE
int		draw_image(mlx_image_t *img, t_cam *cam, t_obj *obj);

//ERROR
void	ft_error(t_data *data, int ecase);

//RAY UTILS
t_ray	new_ray();
t_vec	ray_color(t_ray ray, t_obj *obj, int depth);
t_vec	point_at(t_ray ray, double t);

//VECTOR UTILS
t_vec	*new_vector(double x, double y, double z);
void	print_vector(t_vec vector);
t_vec	add_vector(t_vec v1, t_vec v2);
t_vec	subtract_vector(t_vec v1, t_vec v2);
t_vec	multiply_vector(t_vec v1, t_vec v2);
t_vec	factor_mult_vector(t_vec v1, double f);
t_vec	factor_div_vector(t_vec v1, double f);
double	scalar_vector(t_vec v1, t_vec v2);
t_vec	cross_vector(t_vec v1, t_vec v2);
double	length_vector(t_vec v1);
double	length_squared(t_vec vector);
t_vec	unit_vector(t_vec v1);
t_vec	random_vector(unsigned int max);
t_vec	rand_in_unit_sphere(int seed);
t_vec	rand_in_hemisphere(int seed, t_vec normal);

//HIT_OBJECTS
bool	hit_sphere(t_ray *ray, t_obj *obj);
bool	hit_plane(t_ray *ray, t_obj *obj);

//CAMERA
t_cam	*setup_camera(t_obj *obj, int width, int height);
t_cam	*delete_camera(t_cam *cam);

//COLOR UTILS
int		double_to_color(double r, double g, double b);
int		factor_color(int rgba, double factor);
int		add_color(int c1, int c2);
int		gamma_correction(t_vec color);
t_vec	color_to_vector(uint32_t rgba);
int		vector_to_color(t_vec color);

//UTILS
void	*ft_free(void *pointer);
int xorshift_random(int seed);
int lcg_random(unsigned int seed);
int	xslcg_random(unsigned int seed);
int three_digits(unsigned int seed);

#endif
