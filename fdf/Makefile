NAME	= fdf

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I./libft
LDFLAGS	= -L./lib -L./libft
LDLIBS	= -lft -lm
LINUXLIBS	= -lX11 -lXext -lbsd
X32LIBS	=
X64LIBS	= -lmlx_linux_x64

ARCH = $(shell uname -m)

SRC_PREFIX	= ./src/

SRC	= main draw draw_3dgrid

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX), $(SRC))

OBJ = $(SRC:.c=.o)


.SILENT: $(OBJ)
.PHONY: all clean fclean re libft

all: libft $(NAME)_$(ARCH)


$(NAME)_x86_64: $(OBJ)
	@echo "making $@"
	@$(CC) -o $(NAME) $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(LINUXLIBS) \
		$(X64LIBS) -D LINUX -D BONUS

libft:
	@echo "making $@"
	cd libft && $(MAKE) re

%.o: %.c
	@echo "making $<"
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(LINUXLIBS) \
		$(X64LIBS) -D LINUX -D BONUS

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
