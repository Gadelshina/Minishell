# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/08 16:12:45 by aazrael           #+#    #+#              #
#    Updated: 2022/02/08 16:12:45 by aazrael          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRC			= ft_atoi.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
            ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlcpy.c \
            ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c \
            ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
            ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
            ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
            ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c


OBJ			= $(patsubst %.c,%.o,$(SRC))

CMP			= gcc


FLAGS		= -Wall -Wextra -Werror

all			: $(NAME)

$(NAME)		: $(OBJ)
	ar rcs $(NAME) $?

%.o			: %.c
	$(CMP) $(FLAGS) -c $< -o $@

clean		:
	@rm -f $(OBJ)

fclean		: clean
	@rm -f $(NAME)

re			: fclean all

.PHONY		: all clean fclean re 
