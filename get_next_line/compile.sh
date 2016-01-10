#!/bin/bash

<<<<<<< HEAD
# make -C libft/ fclean && make -C libft/
=======
make -C libft/ fclean && make -C libft/
>>>>>>> 1ad94de832d3e35618b629c25a0d7921c4fac1c0

clang -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
clang -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
clang -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft

# clang -g -o0 -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
# clang -g -o0 -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
# clang -g -o0 -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft
