NAME	= mapper

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I./include
LDFLAGS	= -L./lib -lft
LDLIBS	=

SRC_PREFIX = ./src/

SRC		= main

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX), $(SRC))

OBJ = $(SRC:.c=.o)

.PHONY: all $(NAME) clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

bin/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
