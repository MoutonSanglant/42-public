CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

# Specific compilation routines

ifeq ($(BUILD), Debug)
CFLAGS	+= -g -O0 -D DEBUG
SUFFIX	= .debug.o
else ifeq ($(BUILD), Bonus)
CFLAGS	+= -D BONUS
SUFFIX	= .bonus.o
else
SUFFIX	= .o
endif

NAME	= libftprintf.a

# Get system and set specific flags accordingly

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

SRC_PREFIX = ./src/
OBJ_PREFIX = ./obj/

SRC		= memset bzero memcpy memccpy memmove memchr memcmp strdup strcpy strncpy \
strcat strncat strlcat strchr strrchr strstr strnstr strcmp strncmp atoi \
isalpha isdigit isalnum isascii isprint toupper tolower memalloc memdel strnew \
strdel strclr striter striteri strmap strmapi strequ strnequ strsub strjoin \
strtrim strsplit itoa strlen putchar putstr putnbr putunbr putendl putchar_fd putstr_fd \
putnbr_fd putendl_fd lstnew lstdelone lstdel lstadd lstiter lstmap isupper \
islower isspace pow lstsize dl_lstnew dl_lstfront dl_lstback dl_lstpushfront \
dl_lstpushback dl_lstpopfront dl_lstpopback dl_lstiter dl_lstmap dl_lstsize \
dl_lstclear queuenew queuefront queueback queuepush queuepop queuesize \
stacknew stackpush stackpop stacksize lstgetat putaddr itoa_base printf imaxtoa \
uitoa strprepend print_formated_string print_formated_digit print_formated_hex \
print_formated_unsigned print_formated_space print_formated_char \
print_formated_octal print_formated_pointer strpbrk

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX)ft_, $(SRC))

OBJ = $(subst $(SRC_PREFIX), , $(SRC:.c=$(SUFFIX)))
OBJ := $(addprefix $(OBJ_PREFIX), $(OBJ))

.PHONY: all clean fclean re debug bonus

all: $(NAME)

debug:
	@$(MAKE) BUILD=Debug all

bonus:
	@$(MAKE) BUILD=Bonus all

$(NAME): $(OBJ)
	@echo "making $@"
	@ar rc $@ $^
	@ranlib $(NAME)

$(OBJ_PREFIX)%$(SUFFIX): $(SRC_PREFIX)%.c
	@echo "making $@"
	@mkdir -p $(OBJ_PREFIX)
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -rf $(OBJ_PREFIX)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
