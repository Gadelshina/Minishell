NAME = minishell

OBJ_DIR = object/
SRC_DIR = source/

SRCS = source/main.c 

CC = gcc
FLAGS = -Wall -Wextra -Werror
HEAD_DIR = includes
HEAD = includes/minishell.h
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

LIBFT		= libft/libft.a
LIBFT_DIR	= libft/

all : sub_directory libft $(NAME)

sub_directory :
		@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEAD) $(LIBFT)
		$(CC) $(FLAGS) -I $(HEAD_DIR) -I $(LIBFT_DIR) -c $< -o $@

libft:
		make -C $(LIBFT_DIR)

$(NAME) : $(OBJS)
		$(CC) -o $@ $(FLAGS) $^ -lreadline -L$(LIBFT_DIR) -lft
		@echo "\n ./$(NAME) has been compiled"

clean :
		@rm -rf $(OBJ_DIR)
		make clean -C $(LIBFT_DIR)
fclean : clean
		@rm -rf $(NAME)
		make fclean -C $(LIBFT_DIR)
		@echo "fclean complete"
re : fclean all

.PHONY : all fclean clean re