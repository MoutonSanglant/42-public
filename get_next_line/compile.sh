#!/bin/bash

<<<<<<< HEAD
<<<<<<< HEAD
make -C libft/ fclean && make -C libft/
<<<<<<< HEAD
>>>>>>> 473a4c1ceef83c53b7a01a1e21e1e01665fb855e
=======
>>>>>>> 47bb765... gnl iteration
=======
# make -C libft/ fclean && make -C libft/
>>>>>>> c151902... gnl fixes: 'works with missing \n' + 'bad return value'
=======
make -C libft/ fclean && make -C libft/
>>>>>>> b359515... fix gnl

# clang -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
# clang -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
# clang -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft

clang -g -o0 -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
clang -g -o0 -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
clang -g -o0 -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft
