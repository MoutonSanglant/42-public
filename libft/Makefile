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
EXEC_ALL= test_all
EXEC_IS	= test_is
EXEC_PUT= test_put
EXEC_MEM= test_mem
EXEC_STR= test_str
EXEC_LST= test_lst
EXEC_EXTRA	= test_extra

EXEC = $(EXEC_ALL) $(EXEC_IS) $(EXEC_PUT) $(EXEC_MEM) $(EXEC_STR) $(EXEC_LST) $(EXEC_EXTRA)

.PHONY: all clean fclean re

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -D LIBFT_EXTRA
LDFLAGS	= -L. -lft
LDLIBS	=
#-lbsd

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
stacknew stackpush stackpop stacksize lstgetat

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX)ft_, $(SRC))

OBJ = $(SRC:.c=.o)

all: $(NAME) $(EXEC)

nolib: testclean $(EXEC)

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $(NAME)

$(EXEC_ALL):
	gcc -o $@ $(CFLAGS) __libft_testcases.c $(LDFLAGS) \
 $(LDLIBS) -D TEST_ALL

$(EXEC_MEM):
	gcc -o $@ $(CFLAGS) __libft_testcases.c $(LDFLAGS) \
 $(LDLIBS) -D TEST_MEM

$(EXEC_STR):
	gcc -o $@ $(CFLAGS) __libft_testcases.c $(LDFLAGS) \
 $(LDLIBS) -D TEST_STR

$(EXEC_IS):
	gcc -o $@ $(CFLAGS) __libft_testcases.c $(LDFLAGS) \
 $(LDLIBS) -D TEST_IS

$(EXEC_PUT):
	gcc -o $@ $(CFLAGS) __libft_testcases.c $(LDFLAGS) \
 $(LDLIBS) -D TEST_PUT

$(EXEC_LST):
	gcc -o $@ $(CFLAGS) __libft_testcases.c $(LDFLAGS) \
 $(LDLIBS) -D TEST_LST

$(EXEC_EXTRA):
	gcc -o $@ $(CFLAGS) __libft_testcases.c $(LDFLAGS) \
 $(LDLIBS) -D TEST_EXTRA

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

testclean:
	/bin/rm -f $(EXEC)

clean:
	/bin/rm -f ${OBJ}

fclean: clean testclean
	/bin/rm -f $(NAME)

re: fclean all
