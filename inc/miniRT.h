/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:45:02 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/24 09:51:33 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <libft.h>
# include <MLX42.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	double		fx;
	double		fy;
	double		tx;
	double		ty;
	int			*fc;
	double		llen;
	double		llen1;
	double		llen2;
	double		zoom;
	double		angx;
	double		angy;
	double		angz;
	double		stefa;
}				t_data;
