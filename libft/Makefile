# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/23 12:15:53 by zarachne          #+#    #+#              #
#    Updated: 2021/05/04 17:59:10 by zarachne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libft.a

HEAD = libft.h

SRC =	ft_tolower.c ft_toupper.c ft_isalnum.c\
		ft_isalpha.c ft_isascii.c ft_isdigit.c\
		ft_isprint.c  ft_atoi.c ft_bzero.c\
		ft_memset.c ft_strlen.c ft_strlcpy.c\
		ft_strlcat.c ft_strchr.c ft_strrchr.c\
		ft_strnstr.c ft_strncmp.c ft_memcpy.c\
		ft_memccpy.c ft_memmove.c ft_memchr.c\
		ft_memcmp.c ft_calloc.c ft_strdup.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
		ft_putnbr_fd.c ft_substr.c ft_strjoin.c\
		ft_strtrim.c ft_strmapi.c ft_itoa.c\
		ft_split.c 

SRCB =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c\
		ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
		ft_lstclear.c ft_lstiter.c ft_lstmap.c


FLAGS =	-Wall -Werror -Wextra -std=c99

OBJS =	$(SRC:.c=.o)

OBJB =	$(SRCB:.c=.o)

%.o:	%.c $(HEAD)
	gcc $(FLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS) $(OBJB)
	ar rcs	$(NAME) $(OBJS)

bonus:		$(OBJS) $(OBJB)
	ar rcs	$(NAME) $(OBJS) $(OBJB)

clean:
	rm -f $(OBJS) $(OBJB)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re bonus
