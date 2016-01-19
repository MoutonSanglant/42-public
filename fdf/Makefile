NAME	= fdf

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I./libft
LDFLAGS	= -L./lib -L./libft
LDLIBS	= -lft -lm

ARCH	= $(shell uname -m)
OS		= $(shell uname -s)

ifeq ($(OS), Darwin)
	LDLIBS += -lmlx -framework OpenGL -framework AppKit
endif

ifeq ($(OS)_$(ARCH), Linux_x86_64)
	CFLAGS += -D LINUX
	LDLIBS += -lX11 -lXext -lbsd -lmlx_linux_x64
else ifeq ($(OS), Linux)
	CFLAGS += -D LINUX
	LDLIBS += -lX11 -lXext -lbsd -lmlx_linux_x86
endif

SRC_PREFIX	= ./src/

SRC	= main draw draw_3dgrid set_image_pixel init_grid \
	matrix matrix_math

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX), $(SRC))

OBJ = $(SRC:.c=.o)

.SILENT: $(OBJ)
.PHONY: all clean fclean re libft

all: libft $(NAME)

debug: CFLAGS += -D DEBUG -g -O0
debug: fclean debug_compile
debug_compile: $(OBJ) $(SRC_PREFIX)debug.o
	@echo "call to 'debug' rule"
	$(CC) -o $(NAME) $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS) -D BONUS
	/bin/rm -f $(SRC_PREFIX)debug.o

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
