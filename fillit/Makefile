/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Makefile                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 17:43:58 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/08 17:50:57 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

NAME	= fillit

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I./includes
LDFLAGS	= -L. -lft
LDLIBS	=

SRC_PREFIX = ./src/

SRC		=

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX)ft_, $(SRC))

OBJ = $(SRC:.c=.o)

.PHONY: all $(NAME) clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $(CFLAGS) $(NAME) $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -f ${OBJ}

fclean: clean testclean
	/bin/rm -f $(NAME)

re: fclean all
