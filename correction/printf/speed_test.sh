LIB_PATH=~/42/projects/libftprintf

gcc -o speed_test.out speed_test.c -I${LIB_PATH}/src -L${LIB_PATH} -lftprintf -D $1

time ./speed_test.out > dump

rm speed_test.out
rm dump
