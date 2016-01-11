#!/bin/sh

gcc -Wall -Werror -Wextra -I./libft main.c draw.c draw_3dgrid.c -L. -lmlx -L./libft -lft -framework OpenGL -framework AppKit
