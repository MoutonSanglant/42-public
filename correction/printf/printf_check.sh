#!/bin/bash

echo "WARN: If the script name is not 'printf_check.sh', it won't work.'"

PROGRAM_NAME="libftprintf"
BASE_DIR=${BASH_SOURCE%printf_check.sh}
COMMAND_LINE=${BASE_DIR}test_printf
CFLAGS=

if [[ "$1" == "debug" ]]; then
	COMMAND_LINE="valgrind --leak-check=yes ${COMMAND_LINE}"
	CFLAGS="-g -O0"
fi

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

	while ! [[ -f ${HEADER_PATH}libftprintf.h ]]; do
		read -p "set HEADER_PATH (eg. '~/printf/includes/'): " HEADER_PATH
		HEADER_PATH="`eval echo ${HEADER_PATH//>}`/"
		if ! [[ -f ${HEADER_PATH}libftprintf.h ]]; then
			echo "'${HEADER_PATH}libftprintf.h' doesn't exist"
			continue
		fi
		grep -E "ft_printf" "${HEADER_PATH}libftprintf.h"
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

echo ""
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
echo "[13] Digit"
echo "[14] Pointers"
echo "[15] Char"
echo "[16] Strings"
echo "[17] Wide Char"
echo "[18] Wide Strings"
echo "[19] *Unspecified Behaviour"
echo "[20] *HARDCORE"
echo "=============="
echo "(?) tests with an * are optionnals"
echo ""

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
	DEFINE="-D DIGIT"
elif  [[ "$user_input" == "14" ]]
then
	DEFINE="-D POINTERS"
elif  [[ "$user_input" == "15" ]]
then
	DEFINE="-D CHAR"
elif  [[ "$user_input" == "16" ]]
then
	DEFINE="-D STRINGS"
elif  [[ "$user_input" == "17" ]]
then
	DEFINE="-D WIDE_CHAR"
elif  [[ "$user_input" == "18" ]]
then
	DEFINE="-D WIDE_STRINGS"
elif  [[ "$user_input" == "19" ]]
then
	DEFINE="-D UNSPEC"
elif  [[ "$user_input" == "20" ]]
then
	DEFINE="-D HARDCORE"
else
	exit
fi

gcc ${CFLAGS} -Wall -Werror -Wextra -Wno-format -o ${BASE_DIR}test_printf ${BASE_DIR}main.c -L$LIB_PATH -lftprintf -I${HEADER_PATH} $DEFINE
#gcc ${CFLAGS} -o ${BASE_DIR}test_printf ${BASE_DIR}main.c -L$LIB_PATH -lftprintf -I${HEADER_PATH} $DEFINE

${COMMAND_LINE}

rm ${BASE_DIR}test_printf
rm ${BASE_DIR}ft_out.tmp
rm ${BASE_DIR}printf_out.tmp
