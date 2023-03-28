/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:45:02 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/28 09:32:28 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>		//printf
# include <fcntl.h>		//open
# include <unistd.h>	//write, read, open, close
# include <stdlib.h>	//malloc, free
# include <math.h>
# include <limits.h>	//int max
# include <pthread.h>	//threads, mutex
# include "MLX42.h"
# include "libft.h"

//Standard Window Size if no one is given in the scene
# define WIDTH	800
# define HEIGHT	460

//Quality Configuration
# define STEPSIZE	10		// Amount of Pixel that Camera moves
# define MAX_DEPTH	20		// Amount of Bounce Rays
# define NOT		10		// Amount of Threads

//Ray Configuration
# define T_MIN 0.001
# define T_MAX __DBL_MAX__

//Color and Light Configuration
# define SKY			0		//toggle background
# define LIGHT_RADIUS	15		//point light radius
# define ALBEDO			0.7		//material absorption rate
# define REFLEXION		1		//set reflectivity, unused
# define SOFT_SHADOW	1		//toggles soft shadows

//Debugging
# define MLX 1

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
	RES,
	CIRCLE,
	RECT,
	SQUA
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
	int				type;
	double			radius;
	double			width;
	double			hei_fov;
	t_vec			origin;
	t_vec			vector;
	t_vec			vector2;
	t_vec			color;
	struct s_obj	*next;
}					t_obj;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
	double	closest_t;
	t_obj	*closest_object;
	t_vec	normal;
	int		seed;
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
}			t_map;

typedef struct s_thread
{
	int				id;
	pthread_t		pid;
	struct s_data	*data;
	int				runs;
	t_vec			*pixels;
	t_ray			*ray;
	t_vec			*ambient;
}					t_thread;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_cam			*cam;
	t_map			*map;
	t_obj			*obj;
	int				width;
	int				height;
	t_thread		threads[NOT];
}					t_data;

//PARSING
t_map		*check_input(int argc, char **argv);
void		print_map(t_map *map);
int			ft_isvalue(int c);
int			ft_isspace(int c);
int			theend(char *s);
char		*kill_nltb(char *line);
int			first_iscomment(char *line);
t_obj		*create_obj(t_map *map);
char		**ft_split_p(char *s, char c);
void		get_reso(t_obj *obj, char **split);
void		get_cam(t_obj *obj, char **split);
void		get_ambi(t_obj *obj, char **split);
void		get_light(t_obj *obj, char **split);
void		get_sphere(t_obj *obj, char **split);
void		get_pln(t_obj *obj, char **split);
void		get_cyl(t_obj *obj, char **split);
void		get_circle(t_obj *obj, t_vec vec);
void		get_rect(t_obj *obj, char **split);
void		get_square(t_obj *obj, int dir);
double		ft_atof(char *nbr);
int			pre_field_check(char *line);
int			value_check(char *line);
int			ft_strisdigit(char *str);
int			vector_check(char *str, char **fields, int type);
void		print_error(char *str, int type, int i, char *field);
char		**def_color(void);
void		print_syntax_error(t_obj *obj, char *str);

//RENDERING
void		*thread_routine(void *threads);
bool		hit_object(t_ray *ray, t_obj *obj);
t_vec		*get_ambient_lighting(t_obj *obj);
t_vec		gradient(t_ray *ray);

//MLX
void		my_keyhook(mlx_key_data_t keydata, void *param);
int			mlx_setup(t_obj *obj, t_data *data);
void		run_mlx(t_data *data);

//MULTITHREADING
int			create_threads(t_data *data);
int			remove_threads(t_data *data);
int			cancel_threads(t_data *data);

//ERROR
void		ft_error(t_data *data, int ecase);
void		error_message(int ecase);
void		clean_obj(t_obj *obj);
void		cleanup(t_data *data, int lvl);
void		escape(t_data *data);
void		free_map(t_map *map);

//RAY UTILS
t_ray		bounce_ray(t_ray *original);
bool		front_facing(t_ray ray);
t_vec		ray_color(t_ray *ray, t_obj *obj, int depth);
t_vec		ray_at_light(t_ray *ray, t_obj *obj, t_obj *light);
t_vec		point_at(t_ray ray, double t);
t_ray		*set_ray(t_ray *ray, t_cam *cam, double col, double row);
t_ray		*random_ray(t_ray *ray, t_cam *cam, int col, int row);
t_ray		*cam_ray(t_cam *cam);

//VECTOR UTILS
t_vec		new_vector(double x, double y, double z);
void		print_vector(t_vec vector);
t_vec		add_vector(t_vec v1, t_vec v2);
t_vec		subtract_vector(t_vec v1, t_vec v2);
t_vec		multiply_vector(t_vec v1, t_vec v2);
t_vec		factor_mult_vector(t_vec v1, double f);
t_vec		factor_div_vector(t_vec v1, double f);
double		scalar_vector(t_vec v1, t_vec v2);
t_vec		cross_vector(t_vec v1, t_vec v2);
double		length_vector(t_vec v1);
double		length_squared(t_vec vector);
t_vec		unit_vector(t_vec v1);
t_vec		invert_vector(t_vec vec);
t_vec		random_vector(unsigned int max);
t_vec		rand_in_unit_sphere(int seed);
t_vec		rand_in_hemisphere(int seed, t_vec normal);

//HIT_OBJECTS
bool		hit_sphere(t_ray *ray, t_obj *obj);
bool		hit_plane(t_ray *ray, t_obj *obj);
bool		hit_cylinder(t_ray *ray, t_obj *obj);
bool		hit_circle(t_ray *ray, t_obj *obj);
bool		hit_square(t_ray *ray, t_obj *obj);

//CAMERA
t_cam		*setup_cam(t_obj *obj, int width, int height);

//COLOR UTILS
int			double_to_color(double r, double g, double b);
int			factor_color(int rgba, double factor);
int			add_color(int c1, int c2);
int			gamma_correction(t_vec color);
t_vec		color_to_vector(uint32_t rgba);
int			vector_to_color(t_vec color);
t_vec		color_clamp(t_vec color);

//UTILS
void		*ft_free(void *pointer);
int			xorshift_random(int seed);
int			lcg_random(unsigned int seed);
int			xslcg_random(unsigned int seed);
int			three_digits(unsigned int seed);
double		random_double(unsigned int seed);

#endif
