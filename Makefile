# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 14:11:37 by glukon            #+#    #+#              #
#    Updated: 2022/02/10 11:51:31 by aazrael          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

SRCS =		src/main/main.c	src/main/sig.c src/main/env.c src/helps_f/err.c\
			src/helps_f/free_f.c src/main/init_shell.c src/parser/parsers.c\
			scr/parser/parser_help.c 

OBJS =		$(SRCS:.c=.o)

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror

HEADER =	includes/minishell.h

LIBFT =		libft/libft.a

RM =		rm -f

RDL_FLAGS =	

all:		subsystem $(NAME)

%.o:		%.c $(HEADER) $(LIBFT)
			$(CC) $(CFLAGS) -I includes -I libft -c $< -o $@

subsystem:
			make -C libft

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ -lreadline  -L libft -lft -o $(NAME)

clean:
			$(RM) $(OBJS)
			make clean -C libft

fclean:		clean
			$(RM) $(NAME)
			make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re