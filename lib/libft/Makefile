# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 14:21:20 by rbetz             #+#    #+#              #
#    Updated: 2023/03/03 13:16:23 by rbetz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	libft.a

###			###			COMPILER		###			###
CC		:=	"cc"
CFLAGS	:=	-Wall -Wextra -Werror

###			###			SOURCES			###			###
SRC		:=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c
SRC		+=	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c
SRC		+=	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c
SRC		+=	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c
SRC		+=	ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c
SRC		+=	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c
SRC		+=	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
SRC		+=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c
SRC		+=	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
SRC		+=	ft_atol.c ft_ltoa.c ft_strstr.c ft_strreplace.c ft_strisdigit.c
SRC		+=	ft_printf.c ft_printflibft.c
SRC		+=	get_next_line_bonus.c get_next_line_utils_bonus.c
SRC		+=	ft_first_word.c ft_last_word.c
SRC		+=	ft_arraycount.c ft_free_array.c ft_multijoin_array.c
SRC		+=	ft_close.c ft_strcmp.c
SRC		+=	ft_free_multiple.c ft_multijoin.c

###			###			OBJECTS			###			###
OBJ_D	:=	./obj
SRCOBJ	:=	$(patsubst %.c,$(OBJ_D)/%.o,$(SRC))

###			###			COLORS			###			###
RED = \033[1;31m
GREEN = \033[1;32m
YELL = \033[1;33m
BLUE = \033[1;34m
WHITE = \033[0m

###			###			RULES			###			###
all: $(OBJ_D) $(NAME)

$(NAME): $(SRCOBJ)
	@ar -rcs $(NAME) $^
	@echo "$(RED)--->$(BLUE)Libft is compiled.$(WHITE)"

$(OBJ_D)/%.o: %.c message
	@$(CC) $(CFLAGS) -c $< -o $@

message:
	@echo "$(BLUE)--->$(GREEN)Compiling C Files .....$(WHITE)"

$(OBJ_D):
	@mkdir $@

clean:
	@/bin/rm -rf $(OBJ_D) libft.h.gch

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		/bin/rm -f $(NAME); \
	fi;

re: fclean all

.PHONY: all clean fclean re

.INTERMEDIATE: message