# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 12:38:23 by rbetz             #+#    #+#              #
#    Updated: 2023/02/27 14:06:35 by rbetz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	miniRT

###			###			COMPABILITY		###			###
OS		:=	$(shell uname)
BREWU	:=	/Users/$(USER)/.brewconfig.zsh

###			###			COMPILER		###			###
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
#CFLAGS	+=	-framework Cocoa -framework OpenGL -framework IOKit
CFLAGS	+=	-g #-fsanitize=address

###			###			LIBRARIES		###			###
LIBFT_D	:=	./lib/libft
LIBFT	:=	./lib/libft/libft.a
MLX_D	:=	./lib/MLX42/
MLX_L	:=	$(MLX_D)build/
MLX 	:=	$(MLX_D)/build/libmlx42.a
LIB_MAC	:=	-L $(LIBFT_D) -l ft -L $(MLX_L) -l mlx42 -L ~/.brew/opt/glfw/lib -l glfw
LIB		:=	-L $(LIBFT_D) -l ft -L $(MLX_L) -l mlx42 -l glfw

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
VPATH	:=	src/ src/parsing/ src/utils

SRC_F	:=	miniRT.c
SRC_F	+=	parsing.c print_map.c realloc_map.c
SRC_F	+=	pixels.c
SRC_F	+=	ray.c
SRC_F	+=	vector.c
SRC_F	+=	free.c
SRC_F	+=	color.c
SRC_F	+=	camera.c
SRC_F	+=
SRC_F	+=
SRC_F	+=
SRC_F	+=
SRC_F	+=
SRC_F	+=
SRC_F	+=
SRC_F	+=

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
all: $(LIBFT) $(MLX)
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

$(LIBFT):
	make -j -C $(LIBFT_D)

$(MLX): $(CONFIG)
	make -C $(MLX_L)

$(CONFIG):
	@if [ ! -f "$(CONFIG)" ]; then \
		if [ "$(OS)" = "Linux" ]; then \
			apt-get install -y libglfw3-dev >> /dev/null 2>&1 \
		;else \
			if [ -f $(BREWU) ]; then \
				echo "check brew for glfw"; \
				brew install glfw >> /dev/null 2>&1 \
			;else \
				curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | bash; \
				brew install glfw >> /dev/null 2>&1; \
			fi; \
		fi; \
	fi;

clean:
	@if [ -d "$(OBJ_D)" ]; then \
			$(RM) -rf $(OBJ_D); \
			make fclean -C $(LIBFT_D); \
			make clean -C $(MLX_L); \
			echo "$(YELL)>>>$(RED)Cleaning Objects .....$(WHITE)";else \
			echo "$(YELL)>>>$(GREEN)No Objects to remove.$(WHITE)"; \
	fi;

fclean: clean
	@if [ -f "$(NAME)" ]; then \
			$(RM) -f $(NAME); \
			echo "$(GREEN)>>>$(YELL)Cleaning Exec .....$(WHITE)";else \
			echo "No $(NAME) to remove."; \
	fi;

re: fclean all

.PHONY: all clean fclean re
