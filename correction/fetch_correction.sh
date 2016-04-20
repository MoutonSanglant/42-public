#!/bin/sh

function fetch_fillit
{
	mkdir "fillit"
	curl "https://raw.githubusercontent.com/MoutonSanglant/42-public/master/correction/fillit/fillit_check.sh" -o "./fillit/fillit_check.sh"
	curl "https://raw.githubusercontent.com/MoutonSanglant/42-public/master/correction/fillit/examples.tar" -o "./fillit/examples.tar"
	cd fillit
	tar -xvf ./examples.tar
}

#	curl "https://raw.githubusercontent.com/MoutonSanglant/42-public/master/correction/printf/main.c" -o "./printf/main.c"

echo "[1] fillit"
echo "[2] gnl"
echo "[3] printf"
echo "[4] ls"
#echo "[5] minishell"

read answer

if [[ answer == '1' ]]
then
	fetch_fillit
elif [[ answer == '2' ]]
then
elif [[ answer == '3' ]]
then
elif [[ answer == '4' ]]
then
fi

