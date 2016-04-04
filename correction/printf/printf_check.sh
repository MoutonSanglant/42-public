#make
#make
#make re
#make all
#make fclean
#make
#make clean


EXEC_DIR=..
cur_dir=${PWD}

cd $EXEC_DIR

make
#make debug

cd $cur_dir

gcc -Wall -Werror -Wextra -Wno-format -o crashtest ./main.c -L../ -lftprintf -I../includes
#gcc -g -O0 -Wall -Werror -Wextra -Wno-format -o crashtest ./main.c -L../ -lftprintf -I../includes

./crashtest
#valgrind --track-origins=yes --leak-check=yes ./crashtest

rm crashtest
