/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:24:21 by tdefresn          #+#    #+#             */
/*   Updated: 2015/11/24 18:37:19 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/libft.h"

// string.h: memset,
#include <string.h>

// malloc
#include <stdlib.h>

#define MEMSET_LENGTH 17
#define MEMSET_CHAR 'X'

// extra: printf
#include <stdio.h>

void	test_memset()
{
	char *str;

	str = (char*)malloc(sizeof(char) * 1); //MEMSET_LENGTH);

	printf("== memset ==\n");
	printf(">> system lib test\n");
	memset(str, MEMSET_CHAR, MEMSET_LENGTH);
	printf("%s\n", str);
	printf(">> user lib test\n");
	ft_memset(str, MEMSET_CHAR, MEMSET_LENGTH);
	printf("============\n");
}

int		main(int argc, char **argv)
{
	if (argc < 0 || argv[0][0] == '\0')
		return (1);

	test_memset();
}
