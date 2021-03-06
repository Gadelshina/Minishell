# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 14:11:37 by glukon            #+#    #+#              #
#    Updated: 2022/02/27 10:51:15 by zarachne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

SRCS =		src/main/main.c	src/main/sig.c src/main/env.c src/helps_f/err.c\
			src/helps_f/free_f.c src/main/init_shell.c src/parser/parsers.c\
			src/parser/parser_help.c src/parser/parser_help2.c src/parser/parser_help3.c\
			src/parser/parser_help4.c src/parser/tokens.c src/main/executing.c \
			src/helps_f/utils.c src/redirect/redirect_heredoc.c src/redirect/redirect_output.c \
			src/redirect/redirect.c src/main/struct_pid.c \
			src/builtins/cd.c src/builtins/env.c src/builtins/exit.c src/builtins/pwd.c \
			src/execution/execute_builtins.c src/execution/execute_cmd.c\
			src/builtins/echo.c src/builtins/export.c src/builtins/unset.c\
			src/pipe/execute_pipe.c src/pipe/fd.c src/pipe/multi_pipe.c\
			src/pipe/handle_pipes.c src/pipe/handler_redirect.c src/execution/execute_bin.c\
			src/helps_f/get_next_line.c

OBJS =		$(SRCS:.c=.o)

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror

HEADER =	includes/minishell.h

LIBFT =		libft/libft.a

RM =		rm -f

all:		subsystem $(NAME)

%.o:		%.c $(HEADER) $(LIBFT)
			$(CC) $(CFLAGS) -I includes -I libft -c $< -o $@

subsystem:
			make -C libft

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ -lreadline  -Llibft -lft -o $(NAME)
			@echo "\033[49;34m \n ./$(NAME) has been compiled"
			
clean:
			$(RM) $(OBJS)
			make clean -C libft

fclean:		clean
			$(RM) $(NAME)
			make fclean -C libft
			@echo "\033[49;34m fclean complete"

re:			fclean all

.PHONY:		all clean fclean re