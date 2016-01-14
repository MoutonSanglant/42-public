#!/bin/sh

test_name=("empty" \
	"invalid" \
	"invalid_tetri1" \
	"invalid_tetri2" \
	"invalid_tetri3" \
	"invalid_tetri4" \
	"overflow" \
	"reject" \
	"extra_character" \
	"extra_newline_start" \
	"extra_newline_between" \
	"extra_newline_end" \
	"only_square" \
	"only_one" \
	"only_one2" \
	"only_one3" \
	"only_two" \
	"very_simple" \
	"very_simple2" \
	"very_simple3" \
	"very_simple4" \
	"very_simple5" \
	"very_simple6" \
	"simple" \
	"simple2" \
	"pdf" \
	"valid" \
	"sample1" \
	"sample2" \
	"max" \
	"extra" \
	"extra2" )
test=($'error' `# empty` \
	$'error' `# invalid` \
	$'error' `# invalid_tetri1` \
	$'error' `# invalid_tetri2` \
	$'error' `# invalid_tetri3` \
	$'error' `# invalid_tetri4` \
	$'error' `# overflow` \
	$'error' `# reject` \
	$'error' `# extra_character` \
	$'error' `# extra_newline_start` \
	$'error' `# extra_newline_between` \
	$'error' `# extra_newline_end` \
	$'AA\nAA' `# only_square` \
	$'AA.\nA..\nA..' `# only_one` \
	$'.AA\nAA.\n...' `# only_one2` \
	$'AA.\n.AA\n...' `# only_one3` \
	$'.AA.\nAABB\n.BB.\n....' `# only_two` \
	$'AA.\nABB\nABB' `# very_simple` \
	$'BB.\nBAA\nBAA' `# very_simple2` \
	$'AAA\nABB\n.BB' `# very_simple3` \
	$'ABBBB\nA....\nA....\nA....\n.....' `# very_simple4` \
	$'AAAAB\n....B\n....B\n....B\n.....' `# very_simple4` \
	$'AAA.\nACC.\n.CC.\nBBBB' `# very_simple6` \
	$'AADD\nABBD\nABBD\nCCCC' `# simple` \
	$'AA.BB\nADDBB\nAD...\n.D...\nCCCC.' `# simple2` \
	$'DDAA\nCDDA\nCCCA\nBBBB' `# pdf` \
	$'AABBDD.\nA.BBDD.\nACCCCFF\nEE..FF.\n.EEHHII\n.G.H..I\nGGGH..I' `# valid` \
	$'ABBBB\nACCC.\nA..C.\nADD..\nDD...' `# sample1` \
	$'ABBBB.\nACCCEE\nAFFCEE\nA.FFGG\nHHHDDG\n.HDD.G' `# sample2` \
	$'AABBCCCCDD.\nA.BBEE..DD.\nAFFG.EEHHII\nFFGGGJJHKKI\nLLLL.J.HKKI\nMMNN.JOOPRR\nMM.NNOOPPPR\nQQSSTTUUUUR\nQ.S.TTZZ.VV\nQYS.XXZWWVV\nYYYXX.Z.WW.' `# max` \
	$'ABCDEFG\nABCDEFG\nABCDEFG\nABCDEFG\n.......\n.......\n.......' `# extra` \
	$'ABCDEF\nABCDEF\nABCDEF\nABCDEF\n......\n......' `# extra2` \
	$'.AACCDDBBQ\nAACCDDEEBQ\n.FFGGEE.BQ\nFFGGHHIIIQ\nNNNHHJJIKK\nTNLLJJ.KK.\nTLLMMOOPP.\nTTMMOOPPRR\n.SSUUVVRR.\nSSUUVVWWWW' `# hardcore` )
#	$'AABBDD\nA.BBDD\nACCCC.\nHHEEII\nH.GEEI\nHGGG.I' `# valid` \
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
		printf "your output:\n$output\n"
		printf "expected output:\n${test[$i]}\n"
	fi
	let i++
done
