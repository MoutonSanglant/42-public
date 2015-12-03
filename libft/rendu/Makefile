NAME		= libft.a

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I. -D LIBFT_EXTRA
LDFLAGS		=
LDLIBS		=

SRC_PREFIX = ./

SRC   = memset bzero memcpy memccpy memmove memchr memcmp strdup strcpy \
strncpy strcat strncat strlcat strchr strrchr strstr strnstr strcmp strncmp \
isalpha isdigit isalnum isascii isprint toupper tolower memalloc memdel strnew \
strdel strclr striter striteri strmap strmapi strequ strnequ strsub strjoin \
strlen putchar putstr putnbr putendl putchar_fd putstr_fd putnbr_fd putendl_fd \
isupper islower isspace atoi

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX)ft_, $(SRC))

OBJ = $(SRC:.c=.o)

all: $(NAME) $(EXEC_ALL) $(EXEC_MEM) $(EXEC_STR) $(EXEC_IS)

.PHONY: $(NAME) all clean fclean re

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $(NAME)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
