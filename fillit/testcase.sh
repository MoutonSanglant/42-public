#!/bin/sh

test_name=("empty" \
	"invalid" \
	"overflow" \
	"reject" \
	"only_square" \
	"only_one" \
	"very_simple" \
	"very_simple2" \
	"simple" \
	"sample")
test=($'error' \
	$'error' \
	$'error' \
	$'error' \
	$'##\n##' \
	$'???' \
	$'##.\n###\n###' \
	$'##.\n###\n###' \
	$'####\n####\n####\n####' \
	$'???')

for i in ${!test[@]}
do
	output=$(./fillit examples/${test_name[$i]}.fillit)
	runtime=$((time (./fillit examples/${test_name[$i]}.fillit) 2>&1) | grep ^real)
	runtime=${runtime#"real"}
	runtime="${runtime#"${runtime%%[![:space:]]*}"}"
	if [ "$output" == "${test[$i]}" ]
	then
		if [[ ${runtime:2:1} < 1 ]]
		then
			runtime="\033[1;32m("$runtime")"
		else
			runtime="\033[1;31m("$runtime")"
		fi
		printf "\033[1;32m[OK]\033[0m\t$runtime\033[0m\t${test_name[$i]}\n"
	else	
		printf "\033[1;31m[KO]\033[0m\t\033[1;31m($runtime)\033[0m\t${test_name[$i]}\n"
	fi
	let i++
done
