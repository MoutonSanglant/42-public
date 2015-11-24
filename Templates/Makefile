# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/24 15:51:40 by tdefresn          #+#    #+#              #
#    Updated: 2015/11/24 17:13:55 by tdefresn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG	= libft

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
# LDFLAGS = -L.
# LDLIBS = -lft

OBJS = bla.o

all: $(PROG)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

clean:
	rm ./*.o

fclean: clean
	rm $(EXEC)

re: fclean $(PROG)
