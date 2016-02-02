CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I./libft
LDFLAGS	= -L./lib -L./libft
LDLIBS	= -lft -lm

ifeq ($(BUILD), Debug)
CFLAGS	+= -g -O0 -D DEBUG
SUFFIX	= .debug.o
NAME	= fdf.debug
else
SUFFIX	= .o
NAME	= fdf
endif

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
	matrix matrix_math get_next_line get_vertmap_from_file \
	rasterize camera inverse_matrix projection_matrix identity_matrix

ifeq ($(BUILD), Debug)
SRC += debug
endif

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX), $(SRC))

OBJ = $(SRC:.c=$(SUFFIX))


.PHONY: all clean fclean re libft debug

all: $(NAME)

debug:
	$(MAKE) BUILD=Debug all

$(NAME): $(OBJ) libft/libft.a
	@echo "making $@"
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -D BONUS

libft/libft.a: libft

libft:
	@echo "making $@"
	$(MAKE) -C libft BUILD=$(BUILD)

%$(SUFFIX): %.c
	@echo "making $<"
	@$(CC) -o $@ -c $< $(CFLAGS) -D BONUS

clean:
	/bin/rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	/bin/rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

