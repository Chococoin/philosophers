# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/01 17:26:30 by glugo-mu          #+#    #+#              #
#    Updated: 2025/09/01 18:29:50 by glugo-mu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CC = gcc
NAME = ./main.o
SRC = philo/main.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re