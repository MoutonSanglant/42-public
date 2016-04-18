#make
#make
#make re
#make all
#make fclean
#make
#make clean

#LIBPRINTF_PATH=~/projects/printf
#LIBNAME=ftprintf
LIBPRINTF_PATH=~/projects/libft
LIBNAME=ft
LIBFT_HEADER=$LIBPRINTF_PATH/src

EXEC_DIR=$LIBPRINTF_PATH
cur_dir=${PWD}

cd $EXEC_DIR

make
#make debug

cd $cur_dir

gcc -Wall -Werror -Wextra -Wno-format -o crashtest ./main.c -L$LIBPRINTF_PATH -l$LIBNAME -I$LIBFT_HEADER
#gcc -g -O0 -Wall -Werror -Wextra -Wno-format -o crashtest ./main.c -L../ -lftprintf -I../includes

./crashtest
#valgrind --track-origins=yes --leak-check=yes ./crashtest

rm crashtest
