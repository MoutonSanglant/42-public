# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/24 15:51:40 by tdefresn          #+#    #+#              #
#    Updated: 2015/11/24 18:52:45 by tdefresn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean

NAME	= libft.a
EXEC_ALL= ft_all
EXEC_MEM= ft_mem

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra
LDFLAGS	=
LDLIBS	=

SRC_PREFIX = ./src/

SRC   = memset bzero memcpy memccpy memmove memchr memcmp strdup strcpy strncpy \
strcat strncat strlcat strchr strrchr strstr strnstr strcmp strncmp atoi \
isalpha isdigit isalnum isascii isprint toupper tolower memalloc memdel strnew \
strdel strclr striter striteri strmap strmapi strequ strnequ strsub strjoin \
strtrim strsplit itoa strlen putchar putstr putnbr putendl putchar_fd putstr_fd \
putnbr_fd putendl_fd

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX)ft_, $(SRC))

OBJ = $(SRC:.c=.o)

all: $(NAME) $(EXEC_ALL) $(EXEC_MEM)

$(EXEC_ALL):
	gcc -o $(EXEC_ALL) -I./includes $(CFLAGS) __libft_testcases.c -L. -lft \
-D MEM -D STRING

$(EXEC_MEM):
	gcc -o $(EXEC_MEM) -I./includes $(CFLAGS) __libft_testcases.c -L. -lft \
-D MEM

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $(NAME)

%.o: %.c
	$(CC) -o $@ -I./includes -c $< $(CFLAGS)

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(EXEC_ALL) $(EXEC_MEM)

re: fclean all
