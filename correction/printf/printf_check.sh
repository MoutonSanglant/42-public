#!/bin/bash

echo "WARN: If the script name is not 'printf_check.sh', it won't work.'"

PROGRAM_NAME="libftprintf"
BASE_DIR=${BASH_SOURCE%printf_check.sh}

if [[ -f ${BASE_DIR}${PROGRAM_NAME}.cfg ]]
then
	source ${BASE_DIR}${PROGRAM_NAME}.cfg
else
	while ! [[ -f ${LIB_PATH}Makefile ]]; do
		if [[ "$LIB_PATH" != "" ]]; then
			echo "'${LIB_PATH}Makefile' doesn't exist"
		fi
		read -p "set LIB_PATH (eg. '~/printf'): " LIB_PATH
		LIB_PATH="`eval echo ${LIB_PATH//>}`/"
	done

	while ! [[ -f ${HEADER_PATH}libft.h ]]; do
		read -p "set HEADER_PATH (eg. '~/printf/includes/'): " HEADER_PATH
		HEADER_PATH="`eval echo ${HEADER_PATH//>}`/"
		if ! [[ -f ${HEADER_PATH}libft.h ]]; then
			echo "'${HEADER_PATH}libft.h' doesn't exist"
			continue
		fi
		grep -E "ft_printf" "${HEADER_PATH}libft.h"
		if [[ "$?" != "0" ]]; then
			echo "specified header does not contain 'ft_printf' signature"
			HEADER_PATH=
		fi
	done

	echo "HEADER_PATH=$HEADER_PATH" >> ${BASE_DIR}${PROGRAM_NAME}.cfg
	echo "LIB_PATH=$LIB_PATH" >> ${BASE_DIR}${PROGRAM_NAME}.cfg
fi

make -C $LIB_PATH

DEFINE="-D ALL"

echo "Select Unit Test"
echo "[1] ALL"
echo "[2] Specifiers"
echo "[3] Basic tests"
echo "[4] Multiple specifiers"
echo "[5] Flags"
echo "[6] Width"
echo "[7] Precision"
echo "[8] Length"
echo "[9] Missing specifiers"
echo "[10] Hexadecimal"
echo "[11] Octal"
echo "[12] Unsigned"
echo "[13] Char"
echo "[14] Wide Char"
echo "[15] Digit"
echo "[16] *Unspecified Behaviour"
echo "[17] *HARDCORE"
echo "*optionnal tests"

read user_input

if [[ "$user_input" == "1" ]]
then
	DEFINE="-D ALL"
elif  [[ "$user_input" == "2" ]]
then
	DEFINE="-D SPECIFIERS"
elif  [[ "$user_input" == "3" ]]
then
	DEFINE="-D BASIC"
elif  [[ "$user_input" == "4" ]]
then
	DEFINE="-D MULTI_SPEC"
elif  [[ "$user_input" == "5" ]]
then
	DEFINE="-D FLAGS"
elif  [[ "$user_input" == "6" ]]
then
	DEFINE="-D WIDTH"
elif  [[ "$user_input" == "7" ]]
then
	DEFINE="-D PRECISION"
elif  [[ "$user_input" == "8" ]]
then
	DEFINE="-D LENGTH"
elif  [[ "$user_input" == "9" ]]
then
	DEFINE="-D MISSING"
elif  [[ "$user_input" == "10" ]]
then
	DEFINE="-D HEX"
elif  [[ "$user_input" == "11" ]]
then
	DEFINE="-D OCT"
elif  [[ "$user_input" == "12" ]]
then
	DEFINE="-D UNSIGNED"
elif  [[ "$user_input" == "13" ]]
then
	DEFINE="-D CHAR"
elif  [[ "$user_input" == "14" ]]
then
	DEFINE="-D WIDE_CHAR"
elif  [[ "$user_input" == "15" ]]
then
	DEFINE="-D DIGIT"
elif  [[ "$user_input" == "16" ]]
then
	DEFINE="-D UNSPEC"
elif  [[ "$user_input" == "17" ]]
then
	DEFINE="-D HARDCORE"
else
	exit
fi

gcc -Wall -Werror -Wextra -Wno-format -o ${BASE_DIR}test_printf ${BASE_DIR}main.c -L$LIB_PATH -lftprintf -I${HEADER_PATH} $DEFINE

${BASE_DIR}test_printf

rm ${BASE_DIR}test_printf
rm ${BASE_DIR}ft_out.tmp
rm ${BASE_DIR}printf_out.tmp
