#make
#make
#make re
#make all
#make fclean
#make
#make clean

compare_err() {
	local ls_err="$1"
	local ft_ls_err="$2"
	if [ "$ls_err" != "$ft_ls_err" ]
	then
		printf "\033[1;31mError returns are different (ls: $ls_err, ft_ls: $ft_ls_err)\033[1;0m\n"
	fi
	printf "\n"
}

ls_err=
ft_ls_err=
cur_dir=${PWD}
cd ..
if [ $1 == "debug" ]
then
	make debug
	exec="valgrind ../ft_ls.debug"
else
	make
	#exec="valgrind ../ft_ls.debug"
	exec="../ft_ls"
fi
cd $cur_dir

# test 2: invalid parameter
printf "\n\033[1;32mTest1: invalid parameter\033[1;0m\n"
printf "\033[1;33mls\033[1;0m\n"
ls -J test_folder1 ./test_folder2
ls_err=$?
printf "\033[1;33mft_ls\033[1;0m\n"
$exec -J test_folder1 ./test_folder2
ft_ls_err=$?
compare_err "$ls_err" "$ft_ls_err"

# test 2: invalid folder
printf "\n\033[1;32mTest2: invalid folder\033[1;0m\n"
printf "\033[1;33mls\033[1;0m\n"
ls - invalid_folder -
printf "\033[1;33mft_ls\033[1;0m\n"
$exec - invalid_folder -
compare_err "$ls_err" "$ft_ls_err"

# test 3: misplaced parameter
printf "\n\033[1;32mTest3: misplaced parameter\033[1;0m\n"
printf "\033[1;33mls\033[1;0m\n"
ls test_folder1 -a
printf "\033[1;33mft_ls\033[1;0m\n"
$exec test_folder1 -a

# test 4: -a parameter
printf "\n\033[1;32mTest4: -a parameter\033[1;0m\n"
printf "\033[1;33mls\033[1;0m\n"
ls -a
printf "\033[1;33mft_ls\033[1;0m\n"
$exec -a

#make
#~/.brew/Cellar/valgrind/3.11.0/bin/valgrind --track-origins=yes --leak-check=yes ./crashtest
#./crashtest
#rm crashtest
