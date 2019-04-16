# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/09 16:28:11 by cuzureau          #+#    #+#              #
#    Updated: 2019/01/29 14:16:46 by cuzureau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

NOC=\033[0m
OKC=\033[32m
ERC=\033[31m
WAC=\033[33m

INC_PATH= inc/
OBJ_PATH= obj/
SRC_PATH= src/

NAME	=	libft.a
INC_NAME=	libft.h ft_printf.h
OBJ_NAME=	$(SRC_NAME:.c=.o)
SRC_NAME=	ft_abs.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_islower.c ft_isprint.c ft_isupper.c \
			ft_itoa.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
			ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_nummalloc.c \
			ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
			ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c \
			ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c \
			ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
			ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
			ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
			ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
			ft_strtrim.c ft_swap.c ft_tolower.c ft_toupper.c get_next_line.c \
			ft_printf.c letters.c numbers.c tools.c extra.c \
			ft_strjoinfree.c ft_strlenuntilc.c ft_strndup.c \

INC= $(addprefix $(INC_PATH), $(INC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	@echo "$(WAC)libft$(NOC)	+ obj	$(OKC)[OK]$(NOC)"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "$(WAC)libft$(NOC)	+ lib	$(OKC)[OK]$(NOC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
		@rm -rf $(OBJ_PATH)
		@echo "$(WAC)libft$(NOC)	- obj	$(OKC)[OK]$(NOC)"

fclean: clean
		@rm -rf $(NAME)
		@echo "$(WAC)libft$(NOC)	- lib	$(OKC)[OK]$(NOC)"

re: fclean all

norme:
	@norminette $(SRC) $(INC)

.PHONY: all clean fclean re norme
