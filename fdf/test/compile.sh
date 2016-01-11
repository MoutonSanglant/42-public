#!/bin/sh

gcc -Wall -Werror -Wextra -I./libft main.c -L. -lmlx -L./libft -lft -framework OpenGL -framework AppKit
