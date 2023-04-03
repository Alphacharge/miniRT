# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 12:38:23 by rbetz             #+#    #+#              #
#    Updated: 2023/04/03 11:28:46 by rbetz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	miniRT

###			###			COMPABILITY		###			###
OS		:=	$(shell uname)
CONFIG	:=	/Users/$(USER)/.brewconfig.zsh
BREWU	:=	.brew

###			###			COMPILER		###			###
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror -Ofast
#CFLAGS	+=	-g #-fsanitize=address

###			###			LIBRARIES		###			###
LIBFT_D	:=	./lib/libft
LIBFT	:=	./lib/libft/libft.a
MLX_D	:=	./lib/MLX42/
ifeq ($(OS), Darwin)
	MLX_SD :=	build
else
	MLX_SD :=	build_l
endif
MLX_L	:=	$(MLX_D)$(MLX_SD)
MLX 	:=	$(MLX_D)$(MLX_SD)/libmlx42.a
LIB_MAC	:=	-L $(LIBFT_D) -l ft -L $(MLX_L) -l mlx42 -L ~/$(BREWU)/opt/glfw/lib -l glfw
LIB		:=	-L $(LIBFT_D) -l ft -L $(MLX_L) -l mlx42 -l glfw -lm -ldl -lpthread

###			###			HEADER			###			###
INC_D	:=	./inc
INC_ALL	:=	-I $(INC_D)/ -I $(LIBFT_D) -I $(MLX_D)include/MLX42

ifeq ($(OS), Darwin)
	INC_MAC	:=	$(INC_ALL)
	CFLAGS	+=	$(INC_MAC)
else
	INC		:=	$(INC_ALL)
	CFLAGS	+=	$(INC)
endif

###			###			SOURCES			###			###
VPATH	:=	src/ \
			src/camera \
			src/parsing \
			src/color \
			src/intersection \
			src/memory \
			src/mlx \
			src/parsing \
			src/ray \
			src/rendering \
			src/threads \
			src/utils \
			src/vector

SRC_F	:=	miniRT.c
SRC_F	+=	camera.c
SRC_F	+=	color.c
SRC_F	+=	hit_sphere.c hit_plane.c hit_cylinder.c hit_circle.c hit_square.c
SRC_F	+=	ft_error.c cleanup.c
SRC_F	+=	keyhooks.c setup.c
SRC_F	+=	file_parsing.c print_map.c file_utils.c file_utils_2.c
SRC_F	+=	line_parsing.c ft_split_p.c ft_atof.c
SRC_F	+=	pre_field_check.c line_utils.c pars_error.c
SRC_F	+=	get_resolution.c get_camera.c get_ambient.c get_light.c
SRC_F	+=	get_sphere.c get_plane.c get_cylinder.c get_circle.c get_rect.c
SRC_F	+=	get_square.c insert_vectors.c
SRC_F	+=	ray.c ray_utils.c
SRC_F	+=	hard_shadow.c soft_shadow.c render.c hit_object.c
SRC_F	+=	threads.c
SRC_F	+=	free.c random.c
SRC_F	+=	vector.c arithmetics.c unit_vector.c vector_ops.c

###			###			OBJECTS			###			###
OBJ_D	:=	./obj
OBJ_F	:=	$(patsubst %.c,$(OBJ_D)/%.o,$(SRC_F))

###			###			COLORS			###			###
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELL	=	\033[1;33m
BLUE	=	\033[1;34m
WHITE	=	\033[0m

###			###			RULES			###			###
all: message $(LIBFT) $(MLX)
	@$(MAKE) $(NAME) -j

rt:
	$(RM) -rf $(OBJ_D);
	@$(MAKE) $(NAME) -j

ifeq ($(OS), Darwin)
$(NAME): $(OBJ_D) $(OBJ_F)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_F) $(LIB_MAC)
	@echo "$(RED)>>>$(BLUE)$(NAME) is compiled.$(WHITE)"
else
$(NAME): $(OBJ_D) $(OBJ_F)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_F) $(LIB)
	@echo "$(RED)>>>$(BLUE)$(NAME) is compiled.$(WHITE)"
endif

$(OBJ_D)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_D):
	mkdir $@

message:
	@echo "$(BLUE)---------------------------------------------------------"
	@echo "$(BLUE)|$(RED)\t\t\t\t\t   _ _ _\t$(BLUE)|"
	@echo "$(BLUE)|$(RED)\t\t\t\t\t  /_/_/_/$(YELL)\\ \t$(BLUE)|"
	@echo "$(BLUE)|$(RED)\t\t\t\t\t /_/_/_/$(YELL)\/\\ \t$(BLUE)|"
	@echo "$(BLUE)|$(RED)\t\tmini$(YELL)R$(GREEN)T$(RED)\t\t\t/_/_/_/$(YELL)\/\/\\ \t$(BLUE)|"
	@echo "$(BLUE)|$(GREEN)\tby $(RED)fkernbac $(GREEN)and $(YELL)rbetz$(GREEN)\t\t\_\_\_\$(YELL)/\/\/\t$(BLUE)|"
	@echo "$(BLUE)|$(GREEN)\t\t\t\t\t \_\_\_\$(YELL)/\/\t$(BLUE)|"
	@echo "$(BLUE)|$(GREEN)\t\t\t\t\t  \_\_\_\$(YELL)/\t$(BLUE)|"
	@echo "$(BLUE)---------------------------------------------------------$(WHITE)"


$(LIBFT):
	make -j -C $(LIBFT_D)

$(MLX): $(CONFIG)
	@mkdir $(MLX_L)
	@cmake -S $(MLX_D) -B $(MLX_L)
	make -C $(MLX_L)

$(CONFIG):
	@if [ ! -f "$(CONFIG)" ]; then \
		if [ "$(OS)" = "Linux" ]; then \
			apt-get install -y libglfw3-dev cmake >> /dev/null 2>&1 \
		;else \
			if [ -f $(BREWU) ]; then \
				echo "check brew for glfw and cmake"; \
				brew install glfw cmake \
			;else \
				curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh; \
				source ~/.zshrc; \
				brew install glfw cmake; \
			fi; \
		fi; \
	fi;

clean:
	@if [ -d "$(OBJ_D)" ]; then \
			$(RM) -rf $(OBJ_D); \
			make fclean -C $(LIBFT_D); \
			make clean -C $(MLX_L); \
	fi;

fclean: clean
	@$(RM) -r $(MLX_L);
	@if [ -f "$(NAME)" ]; then \
			$(RM) -f $(NAME); \
	fi;
	@echo "$(RED)All is cleaned$(WHITE)"

re: fclean all

bonus: all

.PHONY: all clean fclean re
