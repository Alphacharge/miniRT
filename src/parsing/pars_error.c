/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:24:12 by rbetz             #+#    #+#             */
/*   Updated: 2023/03/07 11:23:03 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_syntax_error(t_obj *obj, char *str)
{
	obj->type = -1;
	printf("%s Syntax Error\n", str);
}

void	print_error(char *str, int type, int i, char *field)
{
	char	**color;

	color = def_color();
	if (type == CAM)
		printf("Camera %s %c (%s) is not valid\n", str, i + 88, field);
	if (type == AMBI)
		printf("Ambientlight %s %s (%s) is not valid\n", str, color[i], field);
	if (type == LIGHT && !ft_strcmp(str, POS))
		printf("Light %s %c (%s) is not valid\n", str, i + 88, field);
	else if (type == LIGHT && !ft_strcmp(str, COL))
		printf("Light %s %s (%s) is not valid\n", str, color[i], field);
	if (type == SPHERE && !ft_strcmp(str, POS))
		printf("Light %s %c (%s) is not valid\n", str, i + 88, field);
	else if (type == SPHERE && !ft_strcmp(str, COL))
		printf("Light %s %s (%s) is not valid\n", str, color[i], field);
	if (type == PLN && !ft_strcmp(str, COL))
		printf("Plane %s %s (%s) is not valid\n", str, color[i], field);
	else if (type == PLN)
		printf("Plane %s %c (%s) is not valid\n", str, i + 88, field);
	if (type == CYL && !ft_strcmp(str, COL))
		printf("Cylinder %s %s (%s) is not valid\n", str, color[i], field);
	else if (type == CYL)
		printf("Cylinder %s %c (%s) is not valid\n", str, i + 88, field);
}
