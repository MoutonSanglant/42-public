#!/bin/bash

PROGRAM_NAME="gnl"
BASE_DIR=${BASH_SOURCE%compile.sh}

if [[ -f ${BASE_DIR}${PROGRAM_NAME}.cfg ]]
then
	source ${BASE_DIR}${PROGRAM_NAME}.cfg
else
	while ! [[ -f ${PROGRAM_PATH}get_next_line.c ]]; do
		if [[ "$PROGRAM_PATH" != "" ]]; then
			echo "'${PROGRAM_PATH}get_next_line.c' doesn't exist"
		fi
		read -p "set PROGRAM_PATH (eg. '~/${PROGRAM_NAME}/'): " PROGRAM_PATH
		PROGRAM_PATH="`eval echo ${PROGRAM_PATH//>}`/"
	done

	while ! [[ -f ${LIBFT_PATH}Makefile ]]; do
		if [[ "$LIBFT_PATH" != "" ]]; then
			echo "'${LIBFT_PATH}Makefile' doesn't exist"
		fi
		read -p "set LIBFT_PATH (eg. '~/libft/'): " LIBFT_PATH
		LIBFT_PATH="`eval echo ${LIBFT_PATH//>}`/"
	done

	echo "PROGRAM_PATH=$PROGRAM_PATH" >> ${BASE_DIR}${PROGRAM_NAME}.cfg
	echo "LIBFT_PATH=$LIBFT_PATH" >> ${BASE_DIR}${PROGRAM_NAME}.cfg
fi

FLAGS="-Wall -Wextra -Werror"
INCLUDES_FOLDERS="-I ${LIBFT_PATH}src -I ${PROGRAM_PATH}"

# DEBUG MODE
#FLAGS="-g -o0 -Wall -Wextra -Werror"
#INCLUDES_FOLDERS="-I libft/includes -I"

make -C ${LIBFT_PATH} fclean && make -C ${LIBFT_PATH}

clang $FLAGS $INCLUDES_FOLDERS -o ${BASE_DIR}get_next_line.o -c ${PROGRAM_PATH}get_next_line.c
clang $FLAGS $INCLUDES_FOLDERS -o ${BASE_DIR}main.o -c ${BASE_DIR}main.c
clang $FLAGS -o ${BASE_DIR}test_gnl ${BASE_DIR}main.o ${BASE_DIR}get_next_line.o $INCLUDES_FOLDERS -L${LIBFT_PATH} -lft

rm ${BASE_DIR}main.o ${BASE_DIR}get_next_line.o
