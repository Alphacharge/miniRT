/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:45:02 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/24 15:41:49 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <libft.h>
# include <MLX42.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

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
