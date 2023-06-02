# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbetz <rbetz@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 16:33:15 by rbetz             #+#    #+#              #
#    Updated: 2023/06/02 18:13:51 by rbetz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	miniRT

###			###			COMPABILITY		###			###
OS		:=	$(shell uname)

###			###			COMPILER		###			###
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
CFLAGS	+=	-O2 -MMD
#CFLAGS	+=	-g #-fsanitize=address

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
DEP_F	:=	$(patsubst %.c,$(OBJ_D)/%.d,$(SRC_F))

###			###			COLORS			###			###
RED		:=	\033[1;31m
GREEN	:=	\033[1;32m
YELL	:=	\033[1;33m
BLUE	:=	\033[1;34m
WHITE	:=	\033[0m

###			###			LIBRARIES		###			###
LIBFT_D	:=	./lib/libft
LIBFT_F	:=	$(LIBFT_D)/libft.a
LIBFT_U	:=	https://www.github.com/Alphacharge/mylibft

MLX42_D	:=	./lib/MLX42
ifeq ($(OS), Darwin)
	MLX42_BD	:=	$(MLX42_D)/build
else
	MLX42_BD	:=	$(MLX42_D)/build_l
endif
MLX42_F	:=	$(MLX42_BD)/libmlx42.a
MLX42_U	:=	https://www.github.com/codam-coding-college/MLX42

LSAN_D	:=	./lib/LeakSanitizer
LSAN_F	:=	$(LSAN_D)/liblsan.a
LSAN_U	:=	https://www.github.com/mhahnFr/LeakSanitizer

LIB		:=	-L $(LIBFT_D) -l ft -L $(MLX42_BD) -l mlx42

###			###			HEADER			###			###
INC_D	:=	./inc
INC_F	:=	-I $(INC_D) -I $(LIBFT_D) -I $(MLX42_D)/include/MLX42

#Linux/Mac Compability for Leaksanitizer
ifeq ($(OS), Darwin)
ifeq ($(shell test -d $(LSAN_D) && test -f $(LSAN_F) && echo exists), exists)
	INC_F	+=	-Wno-gnu-include-next -I $(LSAN_D)/include
	LIB		+=	-L $(LSAN_D) -llsan -lc++
endif
else ifeq ($(OS), Linux)
ifeq ($(shell test -d $(LSAN_D) && test -f $(LSAN_F) && echo exists), exists)
	INC_F	+=	-Wno-gnu-include-next -I $(LSAN_D)/include
	LIB		+=	-rdynamic -L $(LSAN_D) -llsan -ldl -lstdc++
endif
endif

###			###			COMPABILITY		###			###
#Mac Compability for our programm
ifeq ($(OS), Darwin)
ifeq ($(shell which brew), )
	@echo -e "$(BLUE)Install brew ...$(WHITE)"
	@/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
endif
ifeq ($(shell which cmake), )
	@echo "$(BLUE)Install cmake and glfw...$(WHITE)"
	@brew install -q cmake glfw
endif
	BREW_D	:=	$(shell which brew | cut -d'/' -f1-4)
	LIB	+=	-L $(BREW_D)/opt/glfw/lib -l glfw
endif

#Linux Compability for our programm
ifeq ($(OS), Linux)
	LIB	+=	-lm -ldl -l glfw -lpthread
ifeq ($(shell which cmake), )
	@echo "$(BLUE)Install cmake and glfw...$(WHITE)"
	@apt-get update
	@apt-get install -qq -y libglfw3-dev cmake
endif
endif

###			###			RULES			###			###
#make lsan is downloading lsan if its not.
#every make will be with lsan until a clean occurs.

all: message $(LIBFT_F) $(MLX42_F)
	@$(MAKE) -j $(NAME)

lsan: clean_lsan $(OBJ_D) $(LIBFT_F) $(MLX42_F) $(LSAN_F)
	@$(MAKE) -j $(NAME)

$(NAME): $(OBJ_D) $(OBJ_F)
	$(CC) $(CFLAGS) $(INC_F) -o $(NAME) $(OBJ_F) $(LIB)

$(OBJ_D)/%.o: %.c
	$(CC) $(CFLAGS) $(INC_F) -c $< -o $@

-include $(DEP_F)

$(OBJ_D):
	@git config advice.detachedHead false
	@mkdir -p $@

$(LIBFT_F):
ifneq ($(shell test -d $(LIBFT_D) && echo exists), exists)
	@echo "$(GREEN)Clone libft ...$(WHITE)"
	@git clone -q --branch v1.0.0 --recurse-submodules $(LIBFT_U) $(LIBFT_D)
endif
	@$(MAKE) -j -C $(LIBFT_D)

$(MLX42_F):
ifneq ($(shell test -d $(MLX42_D) && echo exists), exists)
	@echo "$(GREEN)Clone MLX42 ...$(WHITE)"
	@git clone -q --branch v2.3.0 --recurse-submodules $(MLX42_U) $(MLX42_D)
endif
ifneq ($(shell test -d $(MLX42_BD) && echo exists), exists)
	@echo "$(GREEN)Cmake MLX42 ...$(WHITE)"
	@cmake -S $(MLX42_D) -B $(MLX42_BD)
endif
	@$(MAKE) -j -C $(MLX42_BD)

$(LSAN_F):
ifneq ($(shell test -d $(LSAN_D) && echo exists), exists)
	@echo "$(GREEN)Clone LeakSanitizer ...$(WHITE)"
	@git clone -q --branch v1.4 --recursive $(LSAN_U) $(LSAN_D)
endif
	@echo "$(GREEN)Make LeakSanitizer ...$(WHITE)"
	@$(MAKE) -s -C $(LSAN_D)

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

clean_lsan:
	@rm -rf $(OBJ_D)

clean:
	@rm -rf $(OBJ_D)
	@rm -f $(LSAN_F)
	@make fclean -C $(LIBFT_D)
	@make clean -C $(MLX42_BD)

fclean: clean
	@rm -rf $(MLX42_BD)
	@rm -f $(NAME)
	@echo "$(BLUE)--->$(GREEN)Cleaning $(NAME) .....$(WHITE)"
	@echo "$(RED)All is cleaned$(WHITE)"

re: fclean all

bonus: all

.PHONY: all fclean clean re lsan bonus clean_lsan
