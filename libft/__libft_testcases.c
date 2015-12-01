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

// extra: printf
#include <stdio.h>
// strnstr
#include <bsd/string.h>
// is****
#include <ctype.h>


#define MEMSET_LENGTH 17
#define FILL_CHAR 'X'
#define LONG_STR "Je suis une jolie pucelle qui se promene nue dans les champs."

void	putcharII(char *c)
{
	ft_putchar(*c);
}

void	putchar_i(unsigned int idx, char *c)
{
	ft_putnbr(idx);
	ft_putstr(": ");
	ft_putchar(*c);
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

	putchar_i(idx, &c);
	return (c);
}

void		test_striter()
{
	ft_putendl("== striter ==");
	ft_striter("Salut les mecs !\n", &putcharII);
	ft_putendl("== striteri ==");
	ft_striteri("Salut les mecs !\n", &putchar_i);
	ft_putendl("=============");
}

void		test_strmap()
{
	char	*str;
	
	str = "R`ktsZkdrZldbr \t"; 
	ft_putendl("== strmap ==");
	ft_putendl(str);
	str = ft_strmap(str, &putchar_map);
	if (str == NULL)
	{
		ft_putendl_fd("map error", 2);
		ft_putendl("============");
		return;
	}
	free(str);
	ft_putendl("== strmapi ==");
	str = "R`ktsZkdrZldbr \t"; 
	str = ft_strmapi(str, &putchar_mapi);
	if (str == NULL)
	{
		ft_putendl_fd("map error", 2);
		ft_putendl("============");
		return;
	}
	ft_putendl(str);
	free(str);
	ft_putendl("=============");
}

void		test_strequ()
{
	char	*str1;
	char	*str2;

	ft_putendl("== strequ ==");
	str1 = "Hello zougou !\n";
	str2 = "Hello gros zougou !\n";
	if (ft_strequ(str1, str2))
		ft_putendl("Strings match");
	else
		ft_putendl("Strings doesn't match");
	if (ft_strequ(str1, "Hello"))
		ft_putendl("Strings match");
	else
		ft_putendl("Strings doesn't match");
	ft_putendl("== strnequ ==");
	if (ft_strnequ(str1, str2, 6))
		ft_putendl("Strings match");
	else
		ft_putendl("Strings doesn't match");
	if (ft_strnequ(str1, str2, 7))
		ft_putendl("Strings match");
	else
		ft_putendl("Strings doesn't match");
	ft_putendl("=============");
}

void		test_strsub()
{
	char	*str;

	ft_putendl("== strsub ==");
	str = ft_strsub(LONG_STR, 12, 15);
	ft_putendl(str);
	ft_strdel (&str);
	ft_putendl("=============");
}

void		test_strjoin()
{
	char	*str;

	ft_putendl("== strjoin ==");
	str = ft_strjoin("Salut les ", "pancakes !");
	ft_putendl(str);
	ft_strdel(&str);
	ft_putendl("=============");
}

void		test_strtrim()
{
	char	*str;

	ft_putendl("== strtrim ==");
	str = ft_strtrim("      \t\t  \t\n  Salut    \n\n\t\n  _\t les pancakes ! La forme ?    \t");
	if (str == NULL)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		ft_putendl("=============");
		return;
	}
	ft_putstr(str);
	ft_putchar('_');
	ft_putchar('\n');
	ft_strdel(&str);
	str = ft_strtrim("  z      ");
	if (str == NULL)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		ft_putendl("=============");
		return;
	}
	ft_putstr(str);
	ft_putchar('_');
	ft_putchar('\n');
	ft_strdel(&str);
	str = ft_strtrim("  \t ");
	if (str == NULL)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		ft_putendl("=============");
		return;
	}

	ft_putendl(str);
	ft_strdel(&str);
	ft_putendl("=============");
}

void		test_strsplit()
{
	char **str;
	int i;

	ft_putendl("== strsplit ==");
	//str = ft_strsplit("*super*chaine****de* *charactereres*", '*');
	//str = ft_strsplit("*super*chaine****de* *charactereres", '*');
	str = ft_strsplit("\0", '*');
	//str = ft_strsplit("***une* ****vache*_*bleue****", '*');
	if (str == NULL)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		ft_putendl("=============");
		return;
	}
	i = 0;
	while (str[i][0] != '\0')
	{
		ft_putendl(str[i]);
		ft_strdel(&str[i]);
		i++;
	}
	ft_memdel((void**)&str);
	ft_putendl("=============");
}

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
		ft_putendl("malloc: Something went bad, abort");
		return;
	}
	nbr_array = (int *)malloc(sizeof(int) * MEMSET_LENGTH);
	if (nbr_array == NULL)
	{
		ft_putendl("malloc: Something went bad, abort");
		return;
	}

	ft_putendl("== memset ==");
	ft_putendl(">> libc");
	memset(str, FILL_CHAR, MEMSET_LENGTH);
	memset(nbr_array, FILL_CHAR, MEMSET_LENGTH);
	ft_putstr("string: ");
	ft_putendl(str);
	i = 0;
	ft_putstr("int array: ");
	while (i < MEMSET_LENGTH)
		ft_putnbr(nbr_array[i++]);
	ft_putendl("\n>> ft");
	ft_memset(str, FILL_CHAR - 1, MEMSET_LENGTH - 2);
	ft_memset(nbr_array, FILL_CHAR + 1, MEMSET_LENGTH - 2);
	ft_putstr("string: ");
	ft_putendl(str);
	i = 0;
	ft_putstr("int array: ");
	while (i < MEMSET_LENGTH)
		ft_putnbr(nbr_array[i++]);
	ft_putendl("\n============");
	free(nbr_array);
	free(str);
}

void	test_bzero()
{
	char	*str;
	int	str_length;

	str = "Je suis une chaine de test";
	ft_putendl("== bzero ==");
	ft_putendl(">> libc");
	ft_putendl(str);
	str_length = ft_strlen(str);
	str = (char*)malloc(sizeof(char) * str_length);
	str = memset(str, FILL_CHAR, str_length);
	ft_putendl(str);
	bzero(str, ft_strlen(str));
	ft_putendl(str);
	free(str);
	ft_putendl(">> libft");
	str = "Je suis une chaine de test";
	str_length = ft_strlen(str);
	ft_putendl(str);
	str = ft_strnew(sizeof(char) * str_length);
	//str = (char *)malloc(sizeof(char) * ft_strlen(str));
	str = ft_memset(str, FILL_CHAR, str_length);
	ft_putendl(str);
	ft_bzero(str, str_length);
	ft_putendl(str);
	ft_strdel(&str);
	ft_putendl("============");
}

void	test_memcpy()
{
	char	*str;
	char	*dst;
	char	*to;
	int	i;
	int	l;

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
	ft_putendl("============");
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
	//str = ft_;
	
	ft_putendl("====================");
}

void	test_memchr()
{
	char	*str;
	char	*s = "Une chaine*d*etoiles*";

	ft_putendl("== memchr ==");
	ft_putendl(">> libc");
	str = ft_strnew(sizeof(char) * ft_strlen(s));
	str = strcpy(str, s);
	ft_putendl(str);
	str = (char *)memchr(str, '*', 8);
	if (str)
		ft_putendl(str);
	else
		ft_putendl("character not found");
	ft_putendl(">> libft");
	str = ft_strnew(sizeof(char) * ft_strlen(s));
	str = ft_strcpy(str, s);
	ft_putendl(str);
	str = (char *)ft_memchr(str, '*', 8);
	if (str)
		ft_putendl(str);
	else
		ft_putendl("character not found");
	ft_putendl("====================");

}

void	test_memcmp()
{
	ft_putendl("== memchr ==");
	ft_putendl(">> libc");
	ft_putnbr(memcmp("banan*e", "bananae", 18));
	ft_putchar('\n');
	ft_putendl(">> libft");
	ft_putnbr(ft_memcmp("banan*e", "bananae", 18));
	ft_putchar('\n');
	ft_putendl("====================");
}

void		test_memalloc()
{
	char	*str;
	int	*int_array;
	int	i;
	
	ft_putstr("== memalloc/memdel ==\n");
	str = (char *)ft_memalloc(MEMSET_LENGTH);
	int_array = (int *)ft_memalloc(MEMSET_LENGTH * sizeof(int));
	
	if (str == NULL || int_array == NULL)
	{
		ft_putstr_fd("memalloc failed\n", 2);
		ft_putstr("===============\n");
		return;
	}
	ft_putendl(str);
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
	ft_putendl(str);
	i = 0;
	while(i < MEMSET_LENGTH)
		ft_putnbr(int_array[i++]);
	ft_putchar('\n');
	ft_memdel((void**)&str);
	ft_memdel((void**)&int_array);
	if (!str)
		ft_putendl("str is NULL");
	if (!int_array)
		ft_putendl("int_array is NULL");
	ft_putendl("===============");
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
		ft_putendl("=============");
		return;
	}
	ft_putendl(str);
	i = 0;
	while(i < MEMSET_LENGTH)
		str[i++] = FILL_CHAR;
	ft_putendl(str);
	ft_strdel(&str);
	if (!str)
		ft_putendl("str is NULL");
	ft_putendl("=============");
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
	ft_putendl(str);
	ft_strclr(str);
	ft_putendl(str);
	ft_putendl("=============");
}

#define STRCPY_STR "La belle Huguette contait fleurette aux assiettes du Baron von Rocket"

void		test_strcpy()
{
	char	*str;

	ft_putendl("== strcpy / strncpy ==");
	ft_putendl(">> libc");
	str = ft_strnew(sizeof(char) * ft_strlen(STRCPY_STR));
	str = strcpy(str, STRCPY_STR);
	ft_putendl(str);
	str = strncpy(str, "Truc vert", 6);
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
	str = ft_strncpy(str, "Truc vert", 6);
	ft_putendl(str);
	str = ft_strncpy(str, "Petit train", 18);
	ft_putendl(str);
	str = ft_strncpy(str, "Chapeau rouge", 5);
	ft_putendl(str);
	ft_strdel(&str);
	ft_putendl("=============");
}

void		test_strcat()
{
	char	*str;

	ft_putendl("== strcat / strncat ==");
	ft_putendl(">> libc");
	str = ft_strnew(sizeof(char) * 200);
	str = strcpy(str, STRCPY_STR);
	ft_putendl(str);
	str = strcat(str, "Petit singe");
	ft_putendl(str);
	str = strncat(str, "Truc vert", 6);
	ft_putendl(str);
	str = strncat(str, "Petit train", 18);
	ft_putendl(str);
	str = strncat(str, "Chapeau rouge", 5);
	ft_putendl(str);
	ft_strdel(&str);
	ft_putendl(">> libc");
	str = ft_strnew(sizeof(char) * 200);
	str = ft_strcpy(str, STRCPY_STR);
	ft_putendl(str);
	str = ft_strcat(str, "Petit singe");
	ft_putendl(str);
	str = ft_strncat(str, "Truc vert", 6);
	ft_putendl(str);
	str = ft_strncat(str, "Petit train", 18);
	ft_putendl(str);
	str = ft_strncat(str, "Chapeau rouge", 5);
	ft_putendl(str);
	ft_putnbr(ft_strlcat(str, "Tartinette", 200));
	ft_putchar('\n');
	ft_putendl(str);
	ft_putnbr(ft_strlcat(str, " Un truc super long et chiant a lire, mais je ne vous oblige pas car de toute maniere tout ne va pas passer car la chaine de caracteres de destination ne fait pas plus de 200 caracteres et il me semble que cette chaine de caracteres en fait plus de 200.", 200));
	ft_putchar('\n');
	ft_putendl(str);
	ft_strdel(&str);
	ft_putendl("=============");
}

#define STRSEARCH_STR "You know tht power ? Look at ththt * buddy !"
#define STRCMP_N 2

void		test_strsearch()
{
	char	*str;
	char	*str_ptr;
	
	ft_putendl("== strstr/strnstr ==");
	ft_putendl(">> libc");
	str = strdup(STRSEARCH_STR);
	str_ptr = str;
	ft_putendl(str);
	str = strstr(str, "tht *");
	ft_putendl(str);
	str = str_ptr;
	str = strnstr(str, "tht *", 36);
	if (str)
		ft_putendl(str);
	ft_strdel(&str_ptr);
	ft_putendl(">> libft");
	str = ft_strdup(STRSEARCH_STR);
	str_ptr = str;
	ft_putendl(str);
	str = ft_strstr(str, "tht *");
	ft_putendl(str);
	str = str_ptr;
	str = ft_strnstr(str, "tht *", 36);
	if (str) 
		ft_putendl(str);

	ft_strdel(&str_ptr);
	//free(str_ptr);
	ft_putendl("== strcmp/strncmp ==");
	ft_putendl("strcmp");
	ft_putnbr(strcmp("ghi", "ghz"));
	ft_putchar('\n');
	ft_putnbr(strcmp("ghi", "gha"));
	ft_putchar('\n');
	ft_putnbr(strcmp("ghi", "ghi"));
	ft_putchar('\n');
	ft_putnbr(ft_strcmp("ghi", "ghz"));
	ft_putchar('\n');
	ft_putnbr(ft_strcmp("ghi", "gha"));
	ft_putchar('\n');
	ft_putnbr(ft_strcmp("ghi", "ghi"));
	ft_putchar('\n');

	ft_putendl("strncmp");
	ft_putnbr(strncmp("ghi", "ghz", STRCMP_N));
	ft_putchar('\n');
	ft_putnbr(strncmp("ghi", "gha", STRCMP_N));
	ft_putchar('\n');
	ft_putnbr(strncmp("ghi", "ghi", STRCMP_N));
	ft_putchar('\n');
	ft_putnbr(ft_strncmp("ghi", "ghz", STRCMP_N));
	ft_putchar('\n');
	ft_putnbr(ft_strncmp("ghi", "gha", STRCMP_N));
	ft_putchar('\n');
	ft_putnbr(ft_strncmp("ghi", "ghi", STRCMP_N));
	ft_putchar('\n');

	ft_putendl("=============");
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
#endif

}

int		main(int argc, char **argv)
{
	if (argc < 0 || argv[0][0] == '\0')
		return (1);

#ifdef IS_TEST
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
#ifdef STRING
	//test_putnbr();
	//test_putnbr_fd();
	//test_putstr_fd();
	//test_striter();
	/*
	test_strmap();
	test_strequ();
	test_strsub();
	test_strjoin();
	test_strtrim();
	test_strsplit();
	test_strcpy();
	test_strcat();
	*/
	test_strsearch();
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
	//test_memalloc();
	//test_strnew();
	//test_strclr();
	test_memset();
	test_bzero();
	test_memcpy();
	test_memmove();
	test_memchr();
	test_memcmp();
#endif
}
