# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:42:39 by ide-albe          #+#    #+#              #
#    Updated: 2023/06/05 19:31:34 by ide-albe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc -g
NAME		= philo
CFLAGS		= -Wall -Wextra
SRC			= philo_main.c utils_1.c
OBJ			= $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean:
			rm -rf $(OBJ)
			make -C libft clean

fclean:	
			rm -rf $(NAME)
			make -C libft fclean
re:
