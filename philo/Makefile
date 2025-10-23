# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/01 17:26:30 by glugo-mu          #+#    #+#              #
#    Updated: 2025/10/23 10:17:04 by glugo-mu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = philo
SRC = main.c utils.c utils_2.c utils_3.c
CFLAGS = -Werror -Wall -Wextra -g

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re