#make
#make
#make re
#make all
#make fclean
#make
#make clean

if [ "$1" == "out" ]
then
	output="1"
fi

compare_err() {
	local ls_err="$1"
	local ft_ls_err="$2"
	if [ "$ls_err" != "$ft_ls_err" ]
	then
		printf "\033[1;31mError returns are different (ls: $ls_err, ft_ls: $ft_ls_err)\033[1;0m\n"
	fi
}

compare_result() {
	local diff_fd=`diff $1 $2`
	if [ "$diff_fd" != "" ]
	then
		printf "\033[1;33mwarning, results differs on $3\033[1;0m\n"
		if [ "$output" == "1" ]
		then
			printf "$diff_fd\n\n"
		fi
	fi
}

test() {
	printf "\033[1;32m$1\033[1;0m\n"
	ls -1 $2 1> ./tmp/fd1_ls 2> ./tmp/fd2_ls
	ls_err=$?
#	if [ "$output" == "1" ]
#	then
#		printf "\033[1;33mls\033[1;0m\n"
#		cat ./tmp/fd1_ls
#	fi
	$exec $2 1> ./tmp/fd1_ft 2> ./tmp/fd2_ft
	ft_ls_err=$?
#	if [ "$output" == "1" ]
#	then
#		printf "\033[1;33mft_ls\033[1;0m\n"
#		cat ./tmp/fd1_ft
#	fi
	compare_result "./tmp/fd1_ft" "./tmp/fd1_ls" "fd1"
	compare_result "./tmp/fd2_ft" "./tmp/fd2_ls" "fd2"
	compare_err "$ls_err" "$ft_ls_err"
}


ls_err=
ft_ls_err=
cur_dir=${PWD}
cd ..
if [ "$1" == "debug" ]
then
	make debug
	exec="valgrind ../ft_ls.debug"
else
	make
	exec="../ft_ls"
fi
cd $cur_dir
echo $PWD
mkdir tmp

# test 1: invalid parameter
test "Test1 : invalid parameter" "-J test_folder empty_folder"

# test 2: invalid folder
test "Test2 : invalid folder" "- invalid_folder -"

# test 3: misplaced parameter
test "Test3 : misplaced parameter" "test_folder -a"

# test 4: -a parameter
test "Test4 : -a parameter" "-a"

# test 5: -Rl parameter
test "Test5 : -Rl parameter" "-Rl ./recursive"

# test 6: 1 empty folder
test "Test6 : 1 empty folder" "./empty_folder"

# test 6': 1 empty folder with -l
test "Test6': 1 empty folderwith -l" "-l ./empty_folder"

# test 7: 2 empty folders
test "Test7 : 2 empty folders" "./empty_folder ./empty_folder"

# test 7': 2 empty folders with -l
test "Test7': 2 empty folders with -l" "-l ./empty_folder ./empty_folder"

# test 8 : multiple files
test "Test8 : multiple files" "-l ./test_folder/a*"

# test 9 : multiple folders
test "Test9 : multiple folders" "./test_folder/a_folder ./test_folder/empty_folder ./test_folder/folder_of_doom ./test_folder/fold"

# test 10: occurences with same name, param: -lt
test "Test10: occurences with same name, param: -lt" "-lt ./test_folder"

# test 11: occurences with same name, param: -ltr
test "Test11: occurences with same name, param: -ltr" "-ltr ./test_folder"

# test 12: permission denied
test "Test12: permission denied" "/exam"

#test 13: /dev folder, param: -lR
test "Test13: /dev folder, param: -lR" "/dev"

#test 14: / folder
test "Test14: / folder" "/"

#test 15: list / folder twice
test "Test15: list / folder twice" "/ /"

#test 16: Special encodings, params: -lR
test "Test16: Special encodings, params: -lR" "-lR ./test_folder/special/encodings"

#test 16: Hidden folders recursion, params: -lRa
test "Test16: Hidden folders recursion, params: -lRa" "-lRa ./test_folder/"

# Tests to write:
# -same name folder / file
# -same name folder / file on reverse
# -permission denied (/exam)
# folder name should print
#	* whenever there is at least 2 separate results
#	ls a* docs
#	ls docs docs
#	* but shouldn't print for the no_folder result
#	touch -m < -6 month
#	touch -m > +1 hour
#	touch -m 03112342 toto  ==> create a new file 'toto' with m date mars 11 at 23:42
#	special encodings /Applications/Unity/Documentation/en/Manual

#make
#~/.brew/Cellar/valgrind/3.11.0/bin/valgrind --track-origins=yes --leak-check=yes ./crashtest
#./crashtest
#rm crashtest
