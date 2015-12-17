#!/bin/sh

test_name=("empty" \
	"invalid" \
	"overflow" \
	"reject" \
	"extra_character" \
	"extra_newline_start" \
	"extra_newline_between" \
	"extra_newline_end" \
	"only_square" \
	"only_one" \
	"very_simple" \
	"very_simple2" \
	"simple" \
	"simple2" \
	"valid" \
	"sample1" \
	"sample2")
test=($'error' `# empty` \
	$'error' `# invalid` \
	$'error' `# overflow` \
	$'error' `# reject` \
	$'error' `# extra_character` \
	$'error' `# extra_newline_start` \
	$'error' `# extra_newline_between` \
	$'error' `# extra_newline_end` \
	$'AA\nAA' `# only_square` \
	$'AA.\nA..\nA..' `# only_one` \
	$'AA.\nABB\nABB' `# very_simple` \
	$'BB.\nBAA\nBAA' `# very_simple2` \
	$'AADD\nABBD\nABBD\nCCCC' `# simple` \
	$'AA.BB\nADDBB\nAD...\n.D...\nCCCC.' `# simple` \
	$'AABBDD\nA.BBDD\nACCCC.\nHHEEII\nH.GEEI\nHGGG.I' `# valid` \
	$'ABBBB\nACCC.\nA..C.\nADD..\nDD...' `# sample1` \
	$'ABBBB.\nACCCEE\nAFFCEE\nA.FFGG\nHHHDDG\n.HDD.G' `# sample2` )

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
