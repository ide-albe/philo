# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:42:39 by ide-albe          #+#    #+#              #
#    Updated: 2023/10/13 20:40:27 by ide-albe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc -g 
NAME		= philo
CFLAGS		= -Wall -Wextra -Werror
SRC			= philo_main.c utils.c routine.c time.c simulation.c inits.c
OBJ			= $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean:
			rm -rf $(OBJ)

fclean:	
			rm -rf $(NAME)

re: 		fclean all
