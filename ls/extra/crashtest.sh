#make
#make
#make re
#make all
#make fclean
#make
#make clean
cur_dir=${PWD}
cd ..
make debug
#make
cd $cur_dir
gcc -g -O0 -Wall -Werror -Wextra -o crashtest ./main.c -L../ -lft -I../includes
~/.brew/Cellar/valgrind/3.11.0/bin/valgrind --track-origins=yes --leak-check=yes ./crashtest
#./crashtest
rm crashtest
