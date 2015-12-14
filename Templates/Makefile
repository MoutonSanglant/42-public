NAME	=

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I.

SRC_PREFIX = ./src/

SRC	=

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX)ft_, $(SRC))

OBJ = $(SRC:.c=.o)

.SILENT: $(OBJ)
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $(NAME)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -f ${OBJ}

fclean: clean testclean
	/bin/rm -f $(NAME)

re: fclean all
