/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:24:21 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/03 18:25:33 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef TEST_ALL
# define TEST_IS
# define TEST_PUT
# define TEST_STR
# define TEST_MEM
# define TEST_LST
# define TEST_EXTRA
#endif

#define LINUX

#include <libft.h>

// extra: printf
#include <stdio.h>
// is****
#include <ctype.h>

#ifdef LINUX
// strnstr
# include <bsd/string.h>
#endif

#define MEMSET_LENGTH 17
#define FILL_CHAR 'X'
#define LONG_STR "Je suis une jolie demoiselle qui se promene dans le metro."
//#define LONG_STR "Je s"
#define STRCPY_STR "La belle Huguette contait fleurette aux assiettes du Baron von Rocket"

#define STRSEARCH_STR "Le petit toto, a fait un gros rotototo *."
#define STRSEARCH_LAST 32
#define STRCMP_N 2

void		test_putchar()
{
	ft_putendl("== putchar / putchar_fd ==");
	ft_putstr("putchar: ");
	ft_putchar(FILL_CHAR);
	ft_putendl(" (ok)");
	ft_putstr_fd("putchar_fd on filedescriptor 1: ", 1);
	ft_putchar_fd(FILL_CHAR, 1);
	ft_putendl_fd(" (ok)", 1);
	ft_putstr_fd("putchar_fd on filedescriptor 2: ", 2);
	ft_putchar_fd(FILL_CHAR, 2);
	ft_putendl_fd(" (ok)", 2);
	ft_putchar('\n');
}
void		test_putstr()
{
	ft_putendl("== putstr / putstr_fd ==");
	ft_putstr("putstr: ok\n");
	ft_putstr_fd("putstr_fd on filedescriptor 1: ok\n", 1);
	ft_putstr_fd("putstr_fd on filedescriptor 2: ok\n", 2);
	ft_putstr_fd("putstr_fd on filedescriptor 3: ok\n", 3);
	ft_putchar('\n');
}


void		test_putendl()
{
	ft_putendl("== putendl / putendl_fd ==");
	ft_putendl("putendl: ok");
	ft_putendl_fd("putendl_fd on filedescriptor 1: ok", 1);
	ft_putendl_fd("putendl_fd on filedescriptor 2: ok", 2);
	ft_putchar('\n');
}
void		test_putnbr()
{
	ft_putendl("== putnbr / putnbr_fd ==");
	ft_putstr("putnbr(0): "); // 2147483648
	ft_putnbr(0);
	ft_putstr("\nputnbr(2147483647): "); 
	ft_putnbr(2147483647);
	ft_putstr("\nputnbr(-2147483648): ");
	ft_putnbr(-2147483648);

	ft_putstr_fd("\nputnbr_fd(1297320) on filedescriptor 2: ", 2);
	ft_putnbr_fd(1297320, 2);
	ft_putchar('\n');
}

void		test_memset()
{
	char *str;
	int *nbr_array;
	int i;

	ft_putendl("== memset ==");
	ft_putendl(">> libc");
	str = (char *)malloc(sizeof(char) * MEMSET_LENGTH); //MEMSET_LENGTH);
	if (str == NULL)
	{
		ft_putendl("malloc: Something went bad, abort");
		return;
	}
	nbr_array = (int *)malloc(sizeof(int) * MEMSET_LENGTH);
	if (nbr_array == NULL)
	{
		ft_putendl("malloc: Something went bad, abort");
		return;
	}
	memset(str, FILL_CHAR, MEMSET_LENGTH);
	memset(nbr_array, FILL_CHAR, MEMSET_LENGTH);
	ft_putstr("string: ");
	ft_putendl(str);
	memset(str, FILL_CHAR - 1, MEMSET_LENGTH / 2);
	ft_putstr("string: ");
	ft_putendl(str);
	i = 0;
	ft_putstr("int array: ");
	while (i < MEMSET_LENGTH)
	{
		ft_putnbr(nbr_array[i++]);
		if (i < MEMSET_LENGTH - 1)
			ft_putchar(',');
	}
	ft_putchar('\n');
	memset(nbr_array, FILL_CHAR - 1, MEMSET_LENGTH / 2);
	i = 0;
	ft_putstr("int array: ");
	while (i < MEMSET_LENGTH)
	{
		ft_putnbr(nbr_array[i++]);
		if (i < MEMSET_LENGTH - 1)
			ft_putchar(',');
	}
	ft_putchar('\n');
	free(str);
	free(nbr_array);
	
	ft_putendl(">> libft");
	str = (char *)malloc(sizeof(char) * MEMSET_LENGTH); //MEMSET_LENGTH);
	if (str == NULL)
	{
		ft_putendl("malloc: Something went bad, abort");
		return;
	}
	nbr_array = (int *)malloc(sizeof(int) * MEMSET_LENGTH);
	if (nbr_array == NULL)
	{
		ft_putendl("malloc: Something went bad, abort");
		return;
	}
	ft_memset(str, FILL_CHAR, MEMSET_LENGTH);
	ft_memset(nbr_array, FILL_CHAR, MEMSET_LENGTH);
	ft_putstr("string: ");
	ft_putendl(str);
	ft_memset(str, FILL_CHAR - 1, MEMSET_LENGTH / 2);
	ft_memset(nbr_array, FILL_CHAR - 1, MEMSET_LENGTH / 2);
	ft_putstr("string: ");
	ft_putendl(str);

	i = 0;
	ft_putstr("int array: ");
	while (i < MEMSET_LENGTH)
	{
		ft_putnbr(nbr_array[i++]);
		if (i < MEMSET_LENGTH - 1)
			ft_putchar(',');
	}
	ft_putchar('\n');
	i = 0;
	ft_putstr("int array: ");
	while (i < MEMSET_LENGTH)
	{
		ft_putnbr(nbr_array[i++]);
		if (i < MEMSET_LENGTH - 1)
			ft_putchar(',');
	}
	ft_putchar('\n');
	free(str);
	free(nbr_array);
	ft_putchar('\n');
}

void	test_bzero()
{
	char	*s1;
	char	*s2;

	ft_putendl("== bzero ==");
	ft_putendl(">> libc");
	s1 = "Je suis une chaine de test.";
	ft_putstr("string: ");
	ft_putendl(s1);
	s2 = (char*)malloc(sizeof(char) * ft_strlen(s1));
	s2 = strdup(s1);
	s2 = memset(s2, FILL_CHAR, ft_strlen(s2));
	ft_putstr("string: ");
	ft_putendl(s2);
	bzero(s2, ft_strlen(s2));
	ft_putstr("string: ");
	ft_putendl(s2);
	free(s2);
	ft_putendl(">> libft");
	ft_putstr("string: ");
	ft_putendl(s1);
	s2 = (char*)malloc(sizeof(char) * ft_strlen(s1));
	s2 = ft_strdup(s1);
	s2 = ft_memset(s2, FILL_CHAR, ft_strlen(s2));
	ft_putstr("string: ");
	ft_putendl(s2);
	ft_bzero(s2, ft_strlen(s2));
	ft_putstr("string: ");
	ft_putendl(s2);
	ft_putchar('\n');
}

void	test_memcpy()
{
	char	*str;
	char	*dst;
	char	*to;
	int		i;
	int		l;

	ft_putendl("== memcpy/memccpy ==");
	str = "Je suis une autre chaine de test";
	dst = (char *)malloc(sizeof(char) * ft_strlen(str));
	ft_putendl(">> libc");
	ft_putendl(str);
	dst = memcpy(dst, str, 17);
	ft_putendl(dst);
	to = memccpy(dst, str, 't', 17);
	l = (int)to - (int)dst;
	i = 0;
	while (i < l)
		ft_putchar(dst[i++]);
	ft_putchar('\n');
	free(dst);
	
	ft_putendl(">> libft");
	dst = ft_strnew(sizeof(char) * ft_strlen(str));
	ft_putendl(str);
	dst = ft_memcpy(dst, str, 17);
	ft_putendl(dst);
	to = ft_memccpy(dst, str, 't', 17);
	//printf("dst: %p, to: %p", dst, to);
	l = (int)to - (int)dst;
	i = 0;
	while (i < l)
		ft_putchar(dst[i++]);
	ft_putchar('\n');
	ft_strdel(&dst);
	ft_putchar('\n');
}

void	test_memmove()
{
	char *str;
	char *s = "abcdefghijklmnopqrstuvwxyz";
	
	ft_putendl("== memmove ==");
	ft_putendl(">> libc");
	str = ft_strnew(sizeof(char) * ft_strlen(s));
	str = strcpy(str, s);
	str = memmove(&str[5], str, 22);
	ft_putendl(str);
	ft_putendl(">> libft");
	str = ft_strnew(sizeof(char) * ft_strlen(s));
	str = ft_strcpy(str, s);
	str = ft_memmove(&str[5], str, 22);
	ft_putendl(str);
	ft_putchar('\n');
}

void	test_memchr()
{
	char	*str;
	char	*p;

	ft_putendl("== memchr ==");
	ft_putendl(">> libc");
	str = ft_strdup("Une chaine*d*etoiles*");
	ft_putendl(str);
	p = (char *)memchr(str, '*', 8);
	if (p)
		ft_putendl(p);
	else
		ft_putendl("le caractere * n'apparait pas dans les 8 premiers caracteres");
	p = (char *)memchr(str, '*', 11);
	if (p)
		ft_putendl(p);
	else
		ft_putendl("le caractere * n'apparait pas dans les 11 premiers caracteres");
	ft_strdel(&str);
	ft_putendl(">> libft");
	str = ft_strdup("Une chaine*d*etoiles*");
	ft_putendl(str);
	p = (char *)ft_memchr(str, '*', 8);
	if (p)
		ft_putendl(p);
	else
		ft_putendl("le caractere * n'apparait pas dans les 8 premiers caracteres");
	p = (char *)ft_memchr(str, '*', 11);
	if (p)
		ft_putendl(p);
	else
		ft_putendl("le caractere * n'apparait pas dans les 11 premiers caracteres");
	ft_strdel(&str);
	ft_putchar('\n');
}

void	test_memcmp()
{
	ft_putendl("== memcmp ==");
	ft_putendl(">> libc");
	ft_putstr("Banane / banane: ");
	ft_putnbr(memcmp("Banane", "banane", 1));
	ft_putchar('\n');
	ft_putstr("banane / banane: ");
	ft_putnbr(memcmp("banane", "banane", 1));
	ft_putchar('\n');
	ft_putstr("banana / banane: ");
	ft_putnbr(memcmp("banana", "banane", 1));
	ft_putchar('\n');

	ft_putendl(">> libft");
	ft_putstr("Banane / banane: ");
	ft_putnbr(ft_memcmp("Banane", "banane", 1));
	ft_putchar('\n');
	ft_putstr("banane / banane: ");
	ft_putnbr(ft_memcmp("banane", "banane", 1));
	ft_putchar('\n');
	ft_putstr("banana / banane: ");
	ft_putnbr(ft_memcmp("banana", "banane", 1));
	ft_putchar('\n');
	ft_putchar('\n');
}

void		test_strlen()
{
	char *str;

	str = "test_string";
	printf("== strlen ==\n");
	ft_putendl(str);
	ft_putstr("libc: ");
	ft_putnbr(strlen(str));
	ft_putchar('\n');
	ft_putstr("libft: ");
	ft_putnbr(ft_strlen(str));
	ft_putchar('\n');
	ft_putchar('\n');
}

void		test_strdup()
{
}

void		test_strcpy()
{
	char	*str;

	ft_putendl("== strcpy / strncpy ==");
	ft_putendl(">> libc");
	str = ft_strnew(sizeof(char) * ft_strlen(STRCPY_STR));
	str = strcpy(str, STRCPY_STR);
	ft_putendl(str);
	str = strncpy(str, "OOOOOOOOOOOOOOOO", 6);
	ft_putendl(str);
	str = strncpy(str, "Petit train", 18);
	ft_putendl(str);
	str = strncpy(str, "Chapeau rouge", 5);
	ft_putendl(str);
	ft_strdel(&str);
	ft_putendl(">> libc");
	str = ft_strnew(sizeof(char) * ft_strlen(STRCPY_STR));
	str = ft_strcpy(str, STRCPY_STR);
	ft_putendl(str);
	str = ft_strncpy(str, "OOOOOOOOOOOOOOOO", 6);
	ft_putendl(str);
	str = ft_strncpy(str, "Petit train", 18);
	ft_putendl(str);
	str = ft_strncpy(str, "Chapeau rouge", 5);
	ft_putendl(str);
	ft_strdel(&str);
	ft_putchar('\n');
}

void		test_strcat()
{
	char	*str;

	ft_putendl("== strcat / strncat ==");
	ft_putendl(">> libc");
	str = ft_strnew(sizeof(char) * 200);
	str = strcpy(str, STRCPY_STR);
	ft_putendl(str);
	str = strcat(str, "_______");
	ft_putendl(str);
	str = strncat(str, "Un camion", 6);
	ft_putendl(str);
	str = strncat(str, "Petit train", 18);
	ft_putendl(str);
	str = strncat(str, "Chapeau rouge", 5);
	ft_putendl(str);
#ifndef LINUX
	ft_putnbr(strlcat(str, "Tartinettos", 200));
	ft_putchar('\n');
	ft_putendl(str);
	ft_putnbr(strlcat(str, " Un truc super long et chiant a lire, mais je ne vous oblige pas car de toute maniere tout ne va pas passer car la chaine de caracteres de destination ne fait pas plus de 200 caracteres et il me semble que cette chaine de caracteres en fait plus de 200.", 200));
	ft_putchar('\n');
	ft_putendl(str);
#else
	ft_putstr("Missing code: LINUX");
#endif
	ft_strdel(&str);
	ft_putendl(">> libft");
	str = ft_strnew(sizeof(char) * 200);
	str = ft_strcpy(str, STRCPY_STR);
	ft_putendl(str);
	str = ft_strcat(str, "_______");
	ft_putendl(str);
	str = ft_strncat(str, "Un camion", 6);
	ft_putendl(str);
	str = ft_strncat(str, "Petit train", 18);
	ft_putendl(str);
	str = ft_strncat(str, "Chapeau rouge", 5);
	ft_putendl(str);
	ft_putnbr(ft_strlcat(str, "Tartinettos", 200));
	ft_putchar('\n');
	ft_putendl(str);
	ft_putnbr(ft_strlcat(str, " Un truc super long et chiant a lire, mais je ne vous oblige pas car de toute maniere tout ne va pas passer car la chaine de caracteres de destination ne fait pas plus de 200 caracteres et il me semble que cette chaine de caracteres en fait plus de 200.", 200));
	ft_putchar('\n');
	ft_putendl(str);
	ft_strdel(&str);
	ft_putchar('\n');
}

void	test_strchr()
{
	char	*str;
	char	*p;

	ft_putendl("== strchr / strrchr ==");
	ft_putendl(">> libc");
	str = ft_strdup("Une chaine*d*etoiles*bleues*");
	ft_putendl(str);

	p = strchr(str, '*');
	if (p)
		ft_putendl(p);
	else
		ft_putendl("character not found");
	p = strrchr(str, '*');
	if (p)
		ft_putendl(p);
	else
		ft_putendl("character not found");

	printf("test with '\\0':\nlibc: %p\nlibft: %p\n", strchr(str, '\0'), ft_strchr(str, '\0'));
	ft_strdel(&str);
	ft_putendl(">> libft");

	str = ft_strdup("Une chaine*d*etoiles*bleues*");
	ft_putendl(str);
	p = ft_strchr(str, '*');
	if (p)
		ft_putendl(p);
	else
		ft_putendl("character not found");
	p = ft_strrchr(str, '*');
	if (p)
		ft_putendl(p);
	else
		ft_putendl("character not found");
	printf("test with '\\0':\nlibc: %p\nlibft: %p\n", strrchr(str, '\0'), ft_strrchr(str, '\0'));
	ft_strdel(&str);
	ft_putchar('\n');
}

void		test_strsearch()
{
	char	*str;
	char	*str_ptr;
	
	ft_putendl("== strstr/strnstr ==");
	ft_putendl(">> libc");
	str = strdup(STRSEARCH_STR);
	str_ptr = str;
	ft_putendl(str);
	str = strstr(str, "toto *");
	if (str)
		ft_putendl(str);
	else
		ft_putendl("\"toto *\" n'a pas ete trouve dans la chaine");
	str = str_ptr;
#ifndef LINUX
	str = strnstr(str, "toto *", STRSEARCH_LAST);
	if (str)
		ft_putendl(str);
	else
		ft_putendl("\"toto *\" n'a pas ete trouve dans la chaine avant le dernier caractere");
#else
	ft_putstr("Missing code: LINUX");
#endif
	ft_strdel(&str_ptr);
	ft_putendl(">> libft");
	str = ft_strdup(STRSEARCH_STR);
	str_ptr = str;
	ft_putendl(str);
	str = ft_strstr(str, "toto *");
	if (str)
		ft_putendl(str);
	else
		ft_putendl("\"toto *\" n'a pas ete trouve dans la chaine");
	str = str_ptr;
	str = ft_strnstr(str, "toto *", STRSEARCH_LAST);
	if (str) 
		ft_putendl(str);
	else
		ft_putendl("\"toto *\" n'a pas ete trouve dans la chaine avant le dernier caractere");
	ft_strdel(&str_ptr);
	ft_putchar('\n');
	ft_putendl("== strcmp ==");
	ft_putendl("Libc // Libft");
	ft_putstr("Banane / banane: ");
	ft_putnbr(strcmp("Banane", "banane"));
	ft_putstr(" // ");
	ft_putnbr(ft_strcmp("Banane", "banane"));
	ft_putchar('\n');
	ft_putstr("banane / banane: ");
	ft_putnbr(strcmp("banane", "banane"));
	ft_putstr(" // ");
	ft_putnbr(ft_strcmp("banane", "banane"));
	ft_putchar('\n');
	ft_putstr("banane / banana: ");
	ft_putnbr(strcmp("banane", "banana"));
	ft_putstr(" // ");
	ft_putnbr(ft_strcmp("banane", "banana"));
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putendl("== strncmp ==");
	ft_putendl("Libc // Libft");
	ft_putstr("banane / bAnane (");
	ft_putnbr(STRCMP_N);
	ft_putstr("): ");
	ft_putnbr(strncmp("banane", "bAnane", STRCMP_N));
	ft_putstr(" // ");
	ft_putnbr(ft_strncmp("banane", "bAnane", STRCMP_N));
	ft_putchar('\n');
	ft_putstr("banane / banane (");
	ft_putnbr(STRCMP_N);
	ft_putstr("): ");
	ft_putnbr(strncmp("banane", "banane", STRCMP_N));
	ft_putstr(" // ");
	ft_putnbr(ft_strncmp("banane", "banane", STRCMP_N));
	ft_putchar('\n');
	ft_putstr("banane / bbnana (");
	ft_putnbr(STRCMP_N);
	ft_putstr("): ");
	ft_putnbr(strncmp("banane", "bbnana", STRCMP_N));
	ft_putstr(" // ");
	ft_putnbr(ft_strncmp("banane", "bbnana", STRCMP_N));
	ft_putchar('\n');
	ft_putchar('\n');
}

void	test_atoi()
{
	char	*nb;

	ft_putendl("== atoi ==");
	ft_putendl("Libc // Libft");
	nb = "    \
			-998c37 ";
	ft_putnbr(atoi(nb));
	ft_putstr(" // ");
	ft_putnbr(ft_atoi(nb));
	ft_putchar('\n');
	ft_putnbr(atoi("0"));
	ft_putstr(" // ");
	ft_putnbr(ft_atoi("0"));
	ft_putchar('\n');
	ft_putnbr(atoi("871"));
	ft_putstr(" // ");
	ft_putnbr(ft_atoi("871"));
	ft_putchar('\n');
	ft_putnbr(atoi("2147483647"));
	ft_putstr(" // ");
	ft_putnbr(ft_atoi("2147483647"));
	ft_putchar('\n');
	ft_putnbr(atoi("-2147483648"));
	ft_putstr(" // ");
	ft_putnbr(ft_atoi("-2147483648"));
	ft_putchar('\n');
	ft_putchar('\n');
}

void		is_test(int c)
{
	ft_putstr("isalpha(");
	ft_putchar(c);
	ft_putendl(")");
	ft_putstr("libc: ");
	ft_putnbr(isalpha(c));
	ft_putchar('\n');
	ft_putstr("libft: ");
	ft_putnbr(ft_isalpha(c));
	ft_putchar('\n');
	ft_putendl("-------------");
	ft_putstr("isdigit(");
	ft_putchar(c);
	ft_putendl(")");
	ft_putstr("libc: ");
	ft_putnbr(isdigit(c));
	ft_putchar('\n');
	ft_putstr("libft: ");
	ft_putnbr(ft_isdigit(c));
	ft_putchar('\n');
	ft_putendl("-------------");
	ft_putstr("isalnum(");
	ft_putchar(c);
	ft_putendl(")");
	ft_putstr("libc: ");
	ft_putnbr(isalnum(c));
	ft_putchar('\n');
	ft_putstr("libft: ");
	ft_putnbr(ft_isalnum(c));
	ft_putchar('\n');
	ft_putendl("-------------");
	ft_putstr("isascii(");
	ft_putchar(c);
	ft_putendl(")");
	ft_putstr("libc: ");
	ft_putnbr(isascii(c));
	ft_putchar('\n');
	ft_putstr("libft: ");
	ft_putnbr(ft_isascii(c));
	ft_putchar('\n');
	ft_putendl("-------------");
	ft_putstr("isprint(");
	ft_putchar(c);
	ft_putendl(")");
	ft_putstr("libc: ");
	ft_putnbr(isprint(c));
	ft_putchar('\n');
	ft_putstr("libft: ");
	ft_putnbr(ft_isprint(c));
	ft_putchar('\n');
	ft_putendl("-------------");

# ifdef LIBFT_EXTRA
	ft_putstr("islower(");
	ft_putchar(c);
	ft_putendl(")");
	ft_putstr("libc: ");
	ft_putnbr(islower(c));
	ft_putchar('\n');
	ft_putstr("libft: ");
	ft_putnbr(ft_islower(c));
	ft_putchar('\n');
	ft_putendl("-------------");
	ft_putstr("isupper(");
	ft_putchar(c);
	ft_putendl(")");
	ft_putstr("libc: ");
	ft_putnbr(isupper(c));
	ft_putchar('\n');
	ft_putstr("libft: ");
	ft_putnbr(ft_isupper(c));
	ft_putchar('\n');
	ft_putendl("-------------");
	ft_putstr("tolower(");
	ft_putchar(c);
	ft_putendl(")");
	ft_putstr("libc: ");
	ft_putchar(tolower(c));
	ft_putchar('\n');
	ft_putstr("libft: ");
	ft_putchar(ft_tolower(c));
	ft_putchar('\n');
	ft_putendl("-------------");
	ft_putstr("toupper(");
	ft_putchar(c);
	ft_putendl(")");
	ft_putstr("libc: ");
	ft_putchar(toupper(c));
	ft_putchar('\n');
	ft_putstr("libft: ");
	ft_putchar(ft_toupper(c));
	ft_putchar('\n');
#endif
}

void		test_memalloc()
{
	char	*str;
	int	*int_array;
	int	i;
	
	ft_putendl("== memalloc/memdel ==");
	str = (char *)ft_memalloc(MEMSET_LENGTH);
	int_array = (int *)ft_memalloc(MEMSET_LENGTH * sizeof(int));
	
	if (str == NULL || int_array == NULL)
	{
		ft_putendl_fd("memalloc failed", 2);
		ft_putchar('\n');
		return;
	}
	ft_putstr("str: ");
	ft_putendl(str);
	ft_putstr("int: ");
	i = 0;
	while(i < MEMSET_LENGTH)
		ft_putnbr(int_array[i++]);
	ft_putchar('\n');
	i = 0;
	while(i < MEMSET_LENGTH)
	{
		str[i] = FILL_CHAR;
		int_array[i++] = 42;
	}
	ft_putstr("str: ");
	ft_putendl(str);
	ft_putstr("int: ");
	i = 0;
	while(i < MEMSET_LENGTH)
		ft_putnbr(int_array[i++]);
	ft_putchar('\n');
	ft_memdel((void**)&str);
	ft_memdel((void**)&int_array);
	if (!str)
		ft_putendl("str is NULL");
	if (!int_array)
		ft_putendl("int is NULL");
	ft_putchar('\n');
}

void		test_strnew()
{
	char	*str;
	int	i;

	ft_putendl("== strnew/strdel ==");
	str = ft_strnew(MEMSET_LENGTH);
	if (!str)
	{
		ft_putendl_fd("strnew failed", 2);
		ft_putchar('\n');
		return;
	}
	ft_putstr("str: ");
	ft_putendl(str);
	i = 0;
	while(i < MEMSET_LENGTH)
		str[i++] = FILL_CHAR;
	ft_putstr("str: ");
	ft_putendl(str);
	ft_strdel(&str);
	if (!str)
		ft_putendl("str is NULL");
	ft_putchar('\n');
}

void		test_strclr()
{
	char	*str;
	int	i;

	ft_putendl("== strclr ==");
	str = ft_strnew(MEMSET_LENGTH);
	i = 0;
	while (i < MEMSET_LENGTH)
		str[i++] = FILL_CHAR;
	ft_putstr("str: ");
	ft_putendl(str);
	ft_strclr(str);
	ft_putstr("str: ");
	ft_putendl(str);
	ft_strdel(&str);
	ft_putchar('\n');
}

void	putchar_iter(char *c)
{
	ft_putchar(*c);
}

void	putchar_iteri(unsigned int idx, char *c)
{
	ft_putnbr(idx);
	ft_putstr(": ");
	ft_putchar(*c);
	ft_putstr(", ");
}

void		test_striter()
{
	ft_putendl("== striter ==");
	ft_striter("Salut les mecs !\n", &putchar_iter);
	ft_putchar('\n');
	ft_putendl("== striteri ==");
	ft_striteri("Salut les mecs !\n", &putchar_iteri);
	ft_putchar('\n');
}

char	putchar_map(char c)
{
	if (c == 'Z')
		c = ' ';
	else
		c++;

	ft_putchar(c);
	return (c);
}

char	putchar_mapi(unsigned int idx, char c)
{
	if (c == 'Z')
		c = ' ';
	else
		c++;

	putchar_iteri(idx, &c);
	return (c);
}

void		test_strmap()
{
	char	*str;
	
	str = "R`ktsZkdrZldbr \t"; 
	ft_putendl("== strmap ==");
	ft_putstr(str);
	ft_putstr(" => ");
	str = ft_strmap(str, &putchar_map);
	if (str == NULL)
	{
		ft_putendl_fd("map error", 2);
		ft_putchar('\n');
		return;
	}
	free(str);
	ft_putchar('\n');
	ft_putendl("== strmapi ==");
	str = "R`ktsZkdrZldbr \t"; 
	ft_putstr(str);
	ft_putstr(" => ");
	str = ft_strmapi(str, &putchar_mapi);
	if (str == NULL)
	{
		ft_putendl_fd("map error", 2);
		ft_putchar('\n');
		return;
	}
	ft_putchar('\n');
	ft_putendl(str);
	free(str);
	ft_putchar('\n');
}

void		test_strequ()
{
	char	*str1;
	char	*str2;

	ft_putendl("== strequ ==");
	str1 = "Hello zougou !";
	str2 = "Hello gros zougou !";
	ft_putstr(str1);
	ft_putstr(" equ ");
	ft_putstr(str2);
	ft_putendl(" ?");
	if (ft_strequ(str1, str2))
		ft_putendl("Strings match");
	else
		ft_putendl("Strings doesn't match");
	ft_putstr(str1);
	ft_putstr(" equ HELLO");
	ft_putendl(" ?");
	if (ft_strequ(str1, "Hello"))
		ft_putendl("Strings match");
	else
		ft_putendl("Strings doesn't match");
	ft_putchar('\n');
	ft_putendl("== strnequ ==");
	ft_putstr(str1);
	ft_putstr(" equ ");
	ft_putstr(str2);
	ft_putstr(" ? (6 chars max)");
	if (ft_strnequ(str1, str2, 6))
		ft_putendl("Strings match");
	else
		ft_putendl("Strings doesn't match");
	ft_putstr(str1);
	ft_putstr(" equ ");
	ft_putstr(str2);
	ft_putstr(" ? (7 chars max)");
	if (ft_strnequ(str1, str2, 7))
		ft_putendl("Strings match");
	else
		ft_putendl("Strings doesn't match");
	ft_putchar('\n');
}

void		test_strsub()
{
	char	*str;

	ft_putendl("== strsub ==");
	ft_putstr("strsub(start:1, length:4): ");
	ft_putendl(LONG_STR);
	str = ft_strsub(LONG_STR, 1, 4);
	ft_putendl(str);
	ft_strdel (&str);
	ft_putchar('\n');
}

void		test_strjoin()
{
	char	*str;
	char	*strA;
	char	*strB;

	ft_putendl("== strjoin ==");
	strA = "Salut les...";
	strB = " pancakes !";
	ft_putstr("strA: ");
	ft_putendl(strA);
	ft_putstr("strB: ");
	ft_putendl(strB);
	str = ft_strjoin(strA, strB);
	ft_putendl(str);
	ft_strdel(&str);
	ft_putchar('\n');
}

void		test_strtrim()
{
	char	*str;

	ft_putendl("== strtrim ==");
	str = ft_strtrim("      \t\t  \t\n  Salut    \n\n\t  _\t les pancakes ! La forme ?    \t");
	if (str == NULL)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		ft_putchar('\n');
		return;
	}
	ft_putstr("test1: \"");
	ft_putstr(str);
	ft_putendl("\"");
	ft_strdel(&str);
	str = ft_strtrim("wz      ");
	if (str == NULL)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		ft_putchar('\n');
		return;
	}
	ft_putstr("test2: \"");
	ft_putstr(str);
	ft_putendl("\"");
	ft_strdel(&str);
	str = ft_strtrim("  \t ");
	if (str == NULL)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		ft_putchar('\n');
		return;
	}
	ft_putstr("test3: \"");
	ft_putstr(str);
	ft_putendl("\"");
	ft_strdel(&str);
	ft_putchar('\n');
}

void		test_strsplit()
{
	char **str;
	char *s;
	int i;

	ft_putendl("== strsplit ==");
	s = "super*chaine****de* *charactereres***";
	ft_putstr("str: ");
	ft_putendl(s);
	ft_putendl("-----------");
	str = ft_strsplit(s, '*');
	if (str == NULL)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		ft_putchar('\n');
		return;
	}
	i = 0;
	while (str[i][0] != '\0')
	{
		ft_putendl(str[i]);
		ft_strdel(&str[i]);
		i++;
	}
	ft_putendl("-----------");
	ft_memdel((void**)&str);
	s = "|||||||||";
	ft_putstr("str: ");
	ft_putendl(s);
	ft_putendl("-----------");
	str = ft_strsplit(s, '|');
	if (str == NULL)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		ft_putchar('\n');
		return;
	}
	i = 0;
	while (str[i][0] != '\0')
	{
		ft_putendl(str[i]);
		ft_strdel(&str[i]);
		i++;
	}
	ft_putendl("-----------");
	ft_memdel((void**)&str);
	ft_putchar('\n');
}

void		delone(void *content, size_t content_size)
{
	if (content_size > 0)
		ft_memdel(&content);
}

void		putlst(t_list *elem)
{
	ft_putendl(elem->content);
}

int g_i;

t_list		*setelem(t_list *elem)
{
//	t_list	*new_elem;
	int		l;
	char	*str;

	if (g_i > 1)
	{
		free(elem);
		elem = NULL;
		return (elem);
	}
	g_i++;

//	new_elem = (t_list *) malloc(sizeof(t_list));

	l = ft_strlen(elem->content) + 1;
	if (elem->content)
	{
		l += 4;
		str = ft_strnew(l);
		str = ft_strcpy(str, elem->content);
		str = ft_strcat(str, ": ok");
		elem->content = str;
	}
	elem->content_size = l;
	elem->next = NULL;
	return (elem);
}

void		test_lst()
{
	t_list	*list;
	t_list	*node;
	t_list	*new_list;
	t_list	*node2;
	
	node = (t_list *)malloc(sizeof(t_list));
	node->content_size = 9;
	node->content = "Bouuuh !";
	node2 = ft_lstnew("Bizarre", 8);
	list = ft_lstnew("Trop facile", 12);
	ft_lstadd(&list, node);

	ft_lstadd(&node, node2);
	printf("old list (%p):\n", node2);
	ft_lstiter(node2, &putlst);

	new_list = ft_lstmap(node2, &setelem);
	if (new_list)
	{
		printf("new list (%p):\n", new_list);
		ft_lstiter(new_list, &putlst);
	}
	
	printf("old list (%p):\n", node2);
	ft_lstiter(node2, &putlst);
	//ft_putendl(node->next->content);
	//ft_putendl(list->content);
	//ft_lstdelone(&list, &delone);

	//ft_lstdel(&list, &delone); <<--- ca crash !!
	if (new_list)
		ft_lstdel(&new_list, &delone);
}

void		test_extra()
{
	ft_putendl("== pow ==");
	ft_putstr("3^4: ");
	ft_putnbr(ft_pow(3, 4));
	ft_putchar('\n');
	ft_putstr("12^7: ");
	ft_putnbr(ft_pow(12, 7));
	ft_putchar('\n');
	ft_putchar('\n');
}

int		main(int argc, char **argv)
{
	if (argc < 0 || argv[0][0] == '\0')
		return (1);
	ft_putchar('\n');
#ifdef TEST_MEM
	test_memset();
	test_bzero();
	test_memcpy();
	test_memmove();
	test_memchr();
	test_memcmp();
#endif
#ifdef TEST_STR
	test_strlen();
	test_strdup();
	test_strcpy();
	test_strcat();
	test_strchr();
	test_strsearch();
	test_atoi();
#endif
#ifdef TEST_IS
	if (argc < 2)
	{
		ft_putendl_fd("parameter needed: char", 2);
		return (1);
	}
	if (argv[1][0] == '\\')
		is_test((int) '\n');
	else
		is_test((int)argv[1][0]);
#endif
#ifdef TEST_MEM
	test_memalloc();
	test_strnew();
#endif
#ifdef TEST_STR
	test_strclr();
	test_striter();	
	test_strmap();
	test_strequ();
	test_strsub();
	test_strjoin();
	test_strtrim();
	test_strsplit();	
#endif
#ifdef TEST_PUT
	test_putchar();
	test_putstr();
	test_putendl();
	test_putnbr();
#endif
#ifdef TEST_LST
	test_lst();
#endif
#ifdef TEST_EXTRA
	test_extra();
#endif
}
