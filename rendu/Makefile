# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabuchwa <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/09 15:50:58 by mabuchwa          #+#    #+#              #
#    Updated: 2016/01/09 16:14:19 by mabuchwa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fillit

CC	= gcc
CFLAGS	= -g -O0 -Wall -Werror -Wextra -I./

SRC		= ft_bzero ft_check_file ft_get_coor ft_memset ft_get_size ft_putstr \
			ft_resolution ft_up_left main

SRC := $(addsuffix .c, $(SRC))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	$(CC) -o $@ $(CFLAGS) $(SRC)

clean:

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
