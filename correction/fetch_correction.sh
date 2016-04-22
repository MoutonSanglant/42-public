#!/bin/bash

echo "WARN: If the script name is not 'fetch_correction.sh', it won't work.'"

BASE_DIR=${BASH_SOURCE%fetch_correction.sh}

echo $BASE_DIR
# TODO
#  only gnl & fillit are working
#

return ;

function fetch_fillit
{
	echo "fetching 'fillit' correction"
	mkdir ${BASE_DIR}fillit
	curl "https://raw.githubusercontent.com/MoutonSanglant/42-public/master/correction/fillit/fillit_check.sh" -o "${BASE_DIR}fillit/fillit_check.sh"
	curl "https://raw.githubusercontent.com/MoutonSanglant/42-public/master/correction/fillit/examples.tar" -o "${BASE_DIR}fillit/examples.tar"
	chmod 755 ${BASE_DIR}fillit/fillit_check.sh
	tar -xvf ${BASE_DIR}fillit/examples.tar -C ${BASE_DIR}fillit
}

function fetch_gnl
{
	echo "fetching 'gnl' correction"
	mkdir ${BASE_DIR}gnl
	curl "https://raw.githubusercontent.com/MoutonSanglant/42-public/master/correction/gnl/main.c" -o "${BASE_DIR}gnl/main.c"
	curl "https://raw.githubusercontent.com/MoutonSanglant/42-public/master/correction/gnl/compile.sh" -o "${BASE_DIR}gnl/compile.sh"
	chmod 755 ${BASE_DIR}gnl/compile.sh
}

function fetch_printf
{
	echo "fetching 'printf' correction"
	mkdir "${BASE_DIR}printf"
	curl "https://raw.githubusercontent.com/MoutonSanglant/42-public/master/correction/printf/main.c" -o "${BASE_DIR}printf/main.c"
	curl "https://raw.githubusercontent.com/MoutonSanglant/42-public/master/correction/printf/printf_check.sh" -o "${BASE_DIR}printf/printf_check.sh"
	chmod 755 "${BASE_DIR}printf/printf_check.sh"
}

function fetch_ls
{
	echo "not implemented"
}

function fetch_minishell
{
	echo "not implemented"
}


echo "[1] fillit"
echo "[2] gnl"
echo "[3] printf"
echo "[4] ls"
echo "[5] minishell"
echo ""
echo "[0] exit"

read answer

if [[ "$answer" == '1' ]]
then
	fetch_fillit
elif [[ "$answer" == '2' ]]
then
	fetch_gnl
elif [[ "$answer" == '3' ]]
then
	fetch_printf
elif [[ "$answer" == '4' ]]
then
	fetch_ls
elif [[ "$answer" == '5' ]]
then
	fetch_minishell
fi

echo "$answer"
