# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/01 17:26:30 by glugo-mu          #+#    #+#              #
#    Updated: 2025/09/23 21:37:09 by glugo-mu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = ./philo.out
SRC = philo/main.c philo/utils.c philo/utils_2.c philo/utils_3.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re