#!/bin/bash

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
		read -p "set LIB_PATH (eg. '~/printf/'): " LIB_PATH
		LIB_PATH="`eval echo ${LIB_PATH//>}`"
	done

	echo "LIB_PATH=$LIB_PATH" >> ${BASE_DIR}${PROGRAM_NAME}.cfg
fi

make -C $LIB_PATH

gcc -Wall -Werror -Wextra -Wno-format -o ${BASE_DIR}test_printf ${BASE_DIR}main.c -L$LIB_PATH -lftprintf -I${LIB_PATH}src

${BASE_DIR}test_printf

rm ${BASE_DIR}test_printf
rm ${BASE_DIR}ft_out.tmp
rm ${BASE_DIR}printf_out.tmp
