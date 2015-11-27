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

#include <libft.h>

// string.h: memset,
#include <string.h>

// malloc
#include <stdlib.h>

#define MEMSET_LENGTH 17
#define FILL_CHAR 'X'

// extra: printf
#include <stdio.h>

void		test_putnbr_fd()
{
	ft_putnbr_fd(1297320, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(0, 2);
	ft_putchar_fd('\n', 2);
}

void		test_putnbr()
{
	ft_putnbr(5567320);
	ft_putchar('\n');
	ft_putnbr(0);
	ft_putchar('\n');
	ft_putnbr(-32401);
	ft_putchar('\n');
}


void		test_putendl_fd()
{
	ft_putendl_fd("putendl_fd on filedescriptor 1", 1);
	ft_putendl_fd("putendl_fd on filedescriptor 2", 2);
}

void		test_putendl()
{
	char *str;

	str = "test string";
	printf("== putendl ==\n");
	ft_putendl(str);
	printf("============\n");
}

void		test_strlen()
{
	char *str;

	str = "test_string";
	printf("== strlen ==\n");
	ft_putstr(str);
	ft_putstr("\nstring length: ");
	// @todo: add ft_putnbr
	ft_strlen(str);
	ft_putchar('\n');
	printf("============\n");	

}

void		test_putchar_fd()
{
	printf("== putchar_fd ==\n");
	ft_putchar_fd(FILL_CHAR, 1);
	ft_putchar_fd('\n', 1);
	ft_putchar_fd(FILL_CHAR, 2);
	ft_putchar_fd('\n', 2);
	printf("============\n");
}

void		test_putchar()
{
	printf("== putchar ==\n");
	ft_putchar(FILL_CHAR);
	ft_putchar('\n');
	printf("============\n");
}

void		test_putstr()
{
	printf("== putstr ==\n");
	ft_putstr("string test\n");
	printf("============\n");

}

void		test_putstr_fd()
{
	printf("== putstr_fd ==\n");
	ft_putstr_fd("fd: 1\n", 1);
	ft_putstr_fd("fd: 2\n", 2);
	ft_putstr_fd("fd: 3\n", 3);
	printf("============\n");

}

void		test_memset()
{
	char *str;
	int *nbr_array;
	int i;

	str = (char *)malloc(sizeof(char) * MEMSET_LENGTH); //MEMSET_LENGTH);
	if (str == NULL)
	{
		ft_putstr("malloc: Something went bad, abort\n");
		return;
	}
	nbr_array = (int *)malloc(sizeof(int) * MEMSET_LENGTH);
	if (nbr_array == NULL)
	{
		ft_putstr("malloc: Something went bad, abort\n");
		return;
	}

	printf("== memset ==\n");
	printf(">> libc\n");
	memset(str, FILL_CHAR, MEMSET_LENGTH);
	memset(nbr_array, FILL_CHAR, MEMSET_LENGTH);
	printf("string: %s\n", str);
	i = 0;
	printf("int array: ");
	while (i < MEMSET_LENGTH)
		printf("%i,", nbr_array[i++]);
	printf("\n");
	printf(">> ft\n");
	ft_memset(str, FILL_CHAR - 1, MEMSET_LENGTH - 2);
	ft_memset(nbr_array, FILL_CHAR + 1, MEMSET_LENGTH - 2);
	printf("string %s\n", str);
	i = 0;
	printf("int array: ");
	while (i < MEMSET_LENGTH)
		printf("%i,", nbr_array[i++]);
	printf("\n");
	printf("============\n");

	free(nbr_array);
	free(str);
}

int		main(int argc, char **argv)
{
	if (argc < 0 || argv[0][0] == '\0')
		return (1);

#ifdef STRING
	test_putnbr();
	test_putnbr_fd();
	test_putstr_fd();
	/*	
	test_putendl();
	test_putendl_fd();
	test_strlen();
	test_putchar();	
	test_putchar_fd();	
	test_putstr();
	test_putstr_fd();
	test_strlen();
	*/
#endif
#ifdef MEM
	test_memset();
#endif
}
