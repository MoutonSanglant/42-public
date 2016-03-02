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
cd $cur_dir
gcc -Wall -Werror -Wextra -Wno-format -o crashtest ./main.c -L../ -lftprintf -I../includes
#gcc -Wall -Werror -Wextra -o crashtest ./main.c -L../ -lftprintf -I../includes
#valgrind --leak-check=yes ./crashtest
valgrind --leak-check=yes ./crashtest
rm crashtest
