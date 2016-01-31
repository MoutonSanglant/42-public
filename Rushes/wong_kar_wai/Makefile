NAME	= game_2048

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I./libft
LDFLAGS	= -L./libft
LDLIBS	= -lft -lncurses
DFLAGS	= -g -O0 -D DEBUG

ARCH	= $(shell uname -m)
OS		= $(shell uname -s)

ifeq ($(OS), Darwin)
	LDLIBS +=
endif

ifeq ($(OS)_$(ARCH), Linux_x86_64)
	CFLAGS += -D LINUX
	LDLIBS +=
else ifeq ($(OS), Linux)
	CFLAGS += -D LINUX
	LDLIBS +=
endif

SRC_PREFIX	= ./src/

SRC	= main create_window destroy_window refresh_window swap_windows input_handler \
		menu_loop game_loop options_loop putline putcol board_step restart_game \
		fill_random_tile

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX), $(SRC))

OBJ = $(SRC:.c=.o)

.SILENT: $(OBJ)
.PHONY: all clean fclean re libft

all: libft $(NAME)

debug: CFLAGS += $(DFLAGS)
debug: fclean debug_compile
debug_compile: $(OBJ) $(SRC_PREFIX)debug.o
	@echo "call to 'debug' rule"
	$(CC) -o $(NAME) $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS) -D BONUS
#	/bin/rm -f $(SRC_PREFIX)debug.o

$(NAME): $(OBJ)
	@echo "making $@"
	$(CC) -o $(NAME) $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS) -D BONUS

libft:
	@echo "making $@"
	cd libft && $(MAKE)

%.o: %.c
	@echo "making $<"
	$(CC) -o $@ -c $< $(CFLAGS) -D BONUS

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
