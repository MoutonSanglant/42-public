#make
#make
#make re
#make all
#make fclean
#make
#make clean
cur_dir=${PWD}
cd ..
make
cd $cur_dir
gcc -Wall -Werror -Wextra -Wno-format -o crashtest ./main.c -L../ -lftprintf -I../includes
#gcc -Wall -Werror -Wextra -o crashtest ./main.c -L../ -lftprintf -I../includes
./crashtest
