# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/07 17:29:40 by tdefresn          #+#    #+#              #
#    Updated: 2015/12/07 17:29:46 by tdefresn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

.PHONY: all clean fclean re

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -D LIBFT_EXTRA -D DEBUG

SRC_PREFIX = ./src/


SRC		= memset bzero memcpy memccpy memmove memchr memcmp strdup strcpy strncpy \
strcat strncat strlcat strchr strrchr strstr strnstr strcmp strncmp atoi \
isalpha isdigit isalnum isascii isprint toupper tolower memalloc memdel strnew \
strdel strclr striter striteri strmap strmapi strequ strnequ strsub strjoin \
strtrim strsplit itoa strlen putchar putstr putnbr putendl putchar_fd putstr_fd \
putnbr_fd putendl_fd lstnew lstdelone lstdel lstadd lstiter lstmap isupper \
islower isspace pow lstsize dl_lstnew dl_lstfront dl_lstback dl_lstpushfront \
dl_lstpushback dl_lstpopfront dl_lstpopback dl_lstiter dl_lstmap dl_lstsize \
dl_lstclear queuenew queuefront queueback queuepush queuepop queuesize \
stacknew stackpush stackpop stacksize lstgetat putaddr itoa_base

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix ft_, $(SRC))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "making $@"
	@ar rc $@ $^
	@ranlib $(NAME)

%.o: %.c
	@echo "making $@"
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
