# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 14:11:37 by glukon            #+#    #+#              #
#    Updated: 2022/02/15 09:47:59 by aazrael          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

SRCS =		src/main/main.c	src/main/sig.c src/main/env.c src/helps_f/err.c\
			src/helps_f/free_f.c src/main/init_shell.c src/parser/parsers.c\
			src/parser/parser_help.c src/parser/parser_help2.c src/parser/parser_help3.c\
			src/parser/parser_help4.c src/parser/tokens.c 

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