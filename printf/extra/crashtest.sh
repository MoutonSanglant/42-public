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
gcc -g -O0 -Wall -Werror -Wextra -Wno-format -o crashtest ./main.c -L../ -lftprintf -I../includes
~/.brew/Cellar/valgrind/3.11.0/bin/valgrind --track-origins=yes --leak-check=yes ./crashtest
#./crashtest
rm crashtest
