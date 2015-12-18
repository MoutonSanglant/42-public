NAME	= fillit

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I./include
LDFLAGS	= -L./lib -lft
LDLIBS	=

SRC_PREFIX = ./src/

SRC		= main read_tetri_file get_tetriminos_from_buffer \
		get_pattern_id print_grid bruteforce fillit errors

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX), $(SRC))

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

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
