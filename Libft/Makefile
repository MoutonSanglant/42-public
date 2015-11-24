# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/24 15:51:40 by tdefresn          #+#    #+#              #
#    Updated: 2015/11/24 15:55:36 by tdefresn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = libft

CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: fclean $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) -o $(EXEC)

clean:
	rm ./*.o

fclean: clean
	rm $(EXEC)
