#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <locale.h>

#include <libftprintf.h>


#ifdef ALL
# define SPECIFIERS
# define BASIC
# define MULTI_SPEC
# define FLAGS
# define WIDTH
# define PRECISION
# define LENGTH
# define MISSING
# define HEX
# define OCT
# define UNSIGNED
# define DIGIT
# define POINTERS
# define CHAR
# define STRINGS
# define WIDE_CHAR
# define WIDE_STRINGS
# define HARDCORE
//# define MOULITEST
#endif

#define PRINTF_TEST "printf_out.tmp"
#define FT_TEST "ft_out.tmp"
#define STD_OUT "/dev/tty"
#define BUFF_SIZE 1024

void	ft_strdel(char **as)
{
	free(*as);
	*as = NULL;
}

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (str)
	{
		i = 0;
		while (i < size)
			str[i++] = '\0';
		str[i] = '\0';
	}
	return (str);
}

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (*s++ != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_new;
	char	*ptr;

	str_new = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (str_new)
	{
		ptr = str_new;
		while (*s1)
			*ptr++ = *s1++;
		while (*s2)
			*ptr++ = *s2++;
		*ptr++ = '\0';
	}
	return (str_new);
}

char	*to_str(int fd);
void	compare(char *str_std, char *str_ft, int ret_std, int ret_ft, const char *format);

void	test(const char *format);
void	test_i(const char *format, uintmax_t nb);
void	test_s(const char *format, const char *str);
void	test_S(const char *format, const wchar_t *wstr);
void	test_s_s_s(const char *format, const char *s1, const char *s2, const char *s3);
void	test_s_i_s_s(const char *format, const char *s1, int i, const char *s2, const char *s3);
void	test_s_C_d_p_x_S(const char *format, const char *s, uintmax_t C, intmax_t d, void (*p)(void *), intmax_t x, const wchar_t *ws);
void	test_s_S_p_d_D_i_o_O_u_U_x_X_c(const char *format, const char *str, const wchar_t *wstr, const char *ptr, int d, int D, int i, int o, int O, int u, int U, int x, int X, int c);
void	test_s_d_p_S_D_i_o_O_u_U_x_X_c_C(const char *format, const char *s, intmax_t d, const char *p, const wchar_t *S, intmax_t D, intmax_t i, uintmax_t o, uintmax_t O, uintmax_t u, uintmax_t U, uintmax_t x, uintmax_t X, intmax_t c, intmax_t C);

void	full_test(char specifier, int value);

int test_count = 0;
int total_test = 0;
int correct_test = 0;
int correct_output = 0;

typedef int tab[5][5];

int main(void)
{
	wchar_t		*wstr = L"a sample wide string";
	char		*str = "a sample string";
	int			nb = 42;

	int			i = 2147483647;
	long		l = 2147483647;
	long long	ll = 9223372036854775807;
	intmax_t	im = 9223372036854775807;
	char		c = 0;
	wchar_t		C = L'α';

	int full_test_count = 26;
	int full_test_extra = 11;

	(void)wstr;
	(void)str;
	(void)nb;
	(void)i;
	(void)l;
	(void)ll;
	(void)im;
	(void)c;
	(void)C;
	(void)full_test_count;
	(void)full_test_extra;

	setlocale(LC_ALL, "fr_FR.UTF-8");


#ifdef SPECIFIERS
	total_test += 14;
#endif
#ifdef BASIC
	total_test += 4;
#endif
#ifdef MULTI_SPEC
	total_test += 3;
#endif
#ifdef FLAGS
	total_test += 14;
#endif
#ifdef WIDTH
	total_test += 4;
#endif
#ifdef PRECISION
	total_test += 5;
#endif
#ifdef LENGTH
	total_test += 11;
#endif
#ifdef MISSING
	total_test += 7;
#endif
#ifdef HEX
	total_test += (full_test_count + full_test_extra) * 8;
#endif
#ifdef OCT
	total_test += (full_test_count + full_test_extra) * 8;
#endif
#ifdef UNSIGNED
	total_test += (full_test_count + full_test_extra) * 8;
#endif
#ifdef DIGIT
	total_test += full_test_count * 12;
#endif
#ifdef POINTERS
	total_test += 11;
#endif
#ifdef CHAR
	total_test += 34;
#endif
#ifdef STRINGS
	total_test += 12;
#endif
#ifdef WIDE_CHAR
	total_test += 84;
#endif
#ifdef WIDE_STRINGS
	total_test += 5;
#endif
#ifdef UNDEFINED
	total_test += 4;
#endif
#ifdef HARDCORE
	total_test += 21;
#endif

# ifdef SPECIFIERS
	printf("=== SPECIFIERS ===\n");
	test("%%");
	test_s("%s", str);
	test_S("%S", wstr);
	test_s("%p", str);
	test_i("%d", nb);
	test_i("%D", nb);
	test_i("%i", nb);
	test_i("%o", nb);
	test_i("%O", nb);
	test_i("%u", nb);
	test_i("%U", nb);
	test_i("%x", nb);
	test_i("%X", nb);
	test_i("%c", nb);
# endif

# ifdef BASIC
	printf("\n=== BASIC ===\n");
	test("%%i");
	test("%% is a percent symbol");
	test_i("%i is an int", nb);
	test_s("%s", "une chaine avec 'éç' dedans");
# endif

# ifdef MULTI_SPEC
	printf("\n=== MULTIPLE SPECIFIERS ===\n");
	test_s_s_s("%s %s %s", "one", "two", "three");
	test_s_i_s_s("-- %s %C, %s, %s, ok.", "hello", L'該', NULL, "");
	test_s_C_d_p_x_S("%s %C %d %p %x %% %S", "bonjour ", L'該', 42, &free, 42, L"لحم خنزير");
# endif

# ifdef FLAGS
	printf("\n=== FLAGS ===\n");
	test_i("%i", nb);
	test_i("%i", -nb);
	test_i("%-i", nb);
	test_i("%-i", -nb);
	test_i("%+i", nb);
	test_i("%+i", -nb);
	test_i("% i", nb);
	test_i("% i", -nb);
	test_i("%+d", nb);
	test_i("%-+-+d", nb);
	test_i("%+-+-d", nb);
	test_i("%#x", 42);
	test_i("%#X", 42);
	test_i("%#o", 42);
	/*
	test_s("%-10s is a string", "this");
	test_s("%-2.s is a string", "this");
	test_s("%#-2.s is a string", "this");
	test_s("%-10s is a string", "");
	test_s("%#-10s is a string", "");
	test_s("%-5.2s is a string", "");
	test_s("%#-5.2s is a string", "");
	*/
# endif

# ifdef WIDTH
	printf("\n=== WIDTH ===\n");
	test_i("%5i", 42);
	test_i("%5i", -42);
	test_s("%10s", "this");
	test_s("%0s", "this");
# endif

# ifdef PRECISION
	printf("\n=== PRECISION ===\n");
	test_i("%.5i", 42);
	test_i("%.5i", -42);
	test_i("% .5i", 42);
	test_i("% .5i", -42);
	test_s("%.2s is a string", "this");
	/*
	test_s("%5.2s is a string", "this");
	test_s("%5.0s is a string", "this");
	*/
# endif

# ifdef LENGTH
	printf("\n=== LENGTH ===\n");
	test_i("%hi", 44200);
	test_i("%hhi", 44200);
	test_i("%i", 2147483650);
	test_i("%li", 2147483650);
	test_i("%lli", 9223372036854775807);
	test_i("%ji", 9223372036854775807);
	test_i("%zi", 9223372036854775807);
	test_i("%i", 9223372036854775807);
	test_i("%llx", 9223372036854775807);
	test_i("%lu", 4294967296);
	test_i("%ju", 4999999999);
# endif

# ifdef MISSING
	printf("\n=== MISSING SPECIFIER ===\n");
	test("");
	test("%%");
	test("%5%");
	test("%-5%");
	test("%   %");
	test("%+%");
	test("% .3% Hello ! %% % .3%");
# endif

# ifdef HEX
	printf("\n=== HEXADECIMAL ===\n");
	full_test('x', 42);
	full_test('x', -42);
	full_test('x', 0);
	full_test('x', UCHAR_MAX + 42);
	full_test('X', 42);
	full_test('X', -42);
	full_test('X', 0);
	full_test('X', UCHAR_MAX + 42);
# endif

# ifdef OCT
	printf("\n=== OCTAL ===\n");
	full_test('o', 42);
	full_test('o', -42);
	full_test('o', 0);
	full_test('o', UCHAR_MAX + 42);
	full_test('O', 42);
	full_test('O', -42);
	full_test('O', 0);
	full_test('O', UCHAR_MAX + 42);
# endif

# ifdef UNSIGNED
	printf("\n=== UNSIGNED ===\n");
	full_test('u', 42);
	full_test('u', -42);
	full_test('u', 0);
	full_test('u', UCHAR_MAX + 42);
	full_test('U', 42);
	full_test('U', -42);
	full_test('U', 0);
	full_test('U', UCHAR_MAX + 42);
# endif

# ifdef DIGIT
	printf("\n=== DIGIT ===\n");
	full_test('d', 42);
	full_test('d', -42);
	full_test('d', 0);
	full_test('d', UCHAR_MAX + 42);
	full_test('D', 42);
	full_test('D', -42);
	full_test('D', 0);
	full_test('D', UCHAR_MAX + 42);

	full_test('i', 42);
	full_test('i', -42);
	full_test('i', 0);
	full_test('i', UCHAR_MAX + 42);
# endif

# ifdef POINTERS
	printf("\n=== POINTERS ===\n");
	test_s("%p", "constant");
	test_s("%.0p", 0);
	test_s("%.p", 0);
	test_s("%5.p", 0);
	test_i("%9.2p", 1234);
	test_i("%9.2p", 1234567);
	test_i("%2.9p", 1234);
	test_i("%2.9p", 1234567);
	test_i("% p", 42);
	test_i("%+p", 42);
	test_s("{%5p}", 0);
# endif

# ifdef CHAR
	printf("\n=== CHAR ===\n");
	test_i("%10c", 42);
	test_i("%-10c", 42);
	test_i("%#c", 42);
	test_i("%#8c", 42);
	test_i("%#-8c", 42);
	test_i("%#08c", 42);
	test_i("%#-08c", 42);
	test_i("%5c", -42);

	test_i("%+5c", 42);
	test_i("%0+5c", 42);
	test_i("%0+5c", -42);
	test_i("%05c", -42);
	test_i("%-05c", 42);
	test_i("%-05c", -42);
	test_i("%-5c", -42);
	test_i("%-9.6c", 4242);
	test_i("%9.6c", 4242);
	test_i("%.6c", -4242);
	test_i("% 10.5c", 4242);
	test_i("%- 10.5c", 4242);
	test_i("%-07.3c", -42);
	test_i("%-7.4c", -42);
	test_i("%c", -1);
	test_i("% c", -1);
	test_i("%# c", 42);
	test_i("%# .3c", 42);

	printf("-- c = 0 -- (ok if it doesn't work since printf will print a '\\0' character)\n");
	test_i("%.2c", 0);
	test_i("%#.2c", 0);
	test_i("%07.2c", 0);
	test_i("%#c", 0);
	test_i("%#.c", 0);
	test_i("%#.0c", 0);
	test_i("%#5.c", 0);
	test_i("%#5.0c", 0);
# endif

# ifdef STRINGS
	printf("\n=== STRINGS ===\n");
	test_s("%s", "a constant string");
	test_s("%s", NULL);
	test_s("{% s}", NULL);
	test_s("{% s}", "(null)");
	test_s("{% s}", "");
	test_s("[%+s]", 0);
	test_s("[%+s]", "(null)");
	test_s_s_s("%s, %s", "Hello les cocos !", NULL, NULL);
	test_s_s_s("%-11.3s, %-11.6s", "Hello les cocos !", NULL, NULL);
	test_s_s_s("%-11.3s, %-11.0s", "Hello les cocos !", NULL, NULL);
	test_s_s_s("%-3.11s, %-3.11s", "Hello les cocos !", NULL, NULL);
	test_s_s_s("%-s, %-s", "Hello les cocos !", NULL, NULL);

# endif

# ifdef WIDE_CHAR
	printf("\n=== WIDE_CHAR ===\n");

	printf("-- [0x00000000-0x0000007f] (1 byte) --\n");
	test_i("%10C", 42);
	test_i("%-10C", 42);
	test_i("%#C", 42);
	test_i("%#8C", 42);
	test_i("%#-8C", 42);
	test_i("%#08C", 42);
	test_i("%#-08C", 42);
	test_i("%+5C", 42);
	test_i("%0+5C", 42);
	test_i("%-05C", 42);
	test_i("%# C", 42);
	test_i("%# .3C", 42);

	printf("-- [0x00000080-0x000007ff] (2 bytes) --\n");
	test_i("%#13C", 129);
	test_i("%9.6C", 4242);
	test_i("% 10.5C", 4242);
	test_i("%-9.6C", 4242);
	test_i("%- 10.5C", 4242);

	printf("-- [0x00000800-00000xffff] (3 bytes)--\n");
	test_i("%5C", 0x0955);
	test_i("%0+5C", 0x0955);
	test_i("%05C", 0x0955);
	test_i("%-05C", 0x0955);
	test_i("%-5C", 0x0955);
	test_i("%.6C", 0x0955);
	test_i("%-07.3C", 0x0955);
	test_i("%-7.4C", 0x0955);
	test_i("%C",  0x0955);
	test_i("% C",  0x0955);
	printf("-- [0x00010000-0x001fffff] (4 bytes)--\n");
	test_i("%5C", 0x10ffff);
	test_i("%0+5C", 0x10ffff);
	test_i("%05C", 0x10ffff);
	test_i("%-05C", 0x10ffff);
	test_i("%-5C", 0x10ffff);
	test_i("%.6C", 0x10ffff);
	test_i("%-07.3C", 0x10ffff);
	test_i("%-7.4C", 0x10ffff);
	test_i("%C",  0x10ffff);
	test_i("% C",  0x10ffff);
	test_i("%C", L'該');
	test_i("%C", L'ব');
	test_i("%C", L'ݗ');
	test_i("%C", L'ݜ');
	test_i("%C", L'श');
	test_i("%3C", L'ব');
	test_i("%3C", L'ݗ');
	test_i("%3C", L'ݜ');
	test_i("%3C", L'श');

	printf("-- [0x00200000-0x03ffffff] (5 bytes)--\n");
	test_i("%5C", 0x00200045);
	test_i("%0+5C", 0x00200045);
	test_i("%05C", 0x00200045);
	test_i("%-05C", 0x00200045);
	test_i("%-5C", 0x00200045);
	test_i("%.6C", 0x00200045);
	test_i("%-07.3C", 0x00200045);
	test_i("%-7.4C", 0x00200045);
	test_i("%C",  0x00200045);
	test_i("% C",  0x00200045);
	printf("-- [0x04000000-0x7fffffff] (6 bytes)--\n");
	test_i("%5C", 0x04000045);
	test_i("%0+5C", 0x04000045);
	test_i("%05C", 0x04000045);
	test_i("%-05C", 0x04000045);
	test_i("%-5C", 0x04000045);
	test_i("%.6C", 0x04000045);
	test_i("%-07.3C", 0x04000045);
	test_i("%-7.4C", 0x04000045);
	test_i("%C",  0x04000045);
	test_i("% C",  0x04000045);
	printf("-- [0x80000000-0xffffffff] (forbidden)--\n");
	test_i("%5C", 0x80000000);
	test_i("%0+5C", 0x80000000);
	test_i("%05C", 0x80000000);
	test_i("%-05C", 0x80000000);
	test_i("%-5C", 0x80000000);
	test_i("%.6C", 0x80000000);
	test_i("%-07.3C", 0x80000000);
	test_i("%-7.4C", 0x80000000);
	test_i("%C",  0x80000000);
	test_i("% C",  0x80000000);

	printf("-- c = 0 -- (ok if it doesn't work since printf will print a '\\0' character)\n");
	test_i("%#C", 0);
	test_i("%#.C", 0);
	test_i("%#.0C", 0);
	test_i("%#5.C", 0);
	test_i("%#5.0C", 0);
	test_i("%07.2C", 0);
	test_i("%.2C", 0);
	test_i("%#.2C", 0);
# endif

# ifdef WIDE_STRINGS
	printf("\n=== WIDE STRINGS ===\n");
	test_S("%S", L"a constant wide string");
	test_S("%S", NULL);
	test_S("{%30S}", L"我是一只猫。");
	test_S("{%-30S}", L"我是一只猫。");
	test_S("%-17S", L"বशݜݗ");
# endif

# ifdef HARDCORE
	printf("\n=== HARDCORE ===\n");
	test_i("%jx", -4294967296);
	test_i("%jx", -4294967297);
	test_i("%010x", 542);
	test_i("%08x", 42);
	test_i("%hhd", 128);
	test_i("%hhd", -129);
	test_i("%zhd", 4294967296);
	test_i("%jhd", 9223372036854775807);
	test("\n");
	test("%%");
	test_i("%d", 42);
	test_i("%ld", l);
	test_i("%lld", ll);
	test_i("%c", 75);
	test_i("%C", 8000);
	test_i("%C", 80000);
	test_i("%C", L'α');
	test_s("{%5p}",  0);
	test_s("{%-15p}", 0);
	test("{%10RN}");
	test_s_d_p_S_D_i_o_O_u_U_x_X_c_C("%s%d%p%%%S%D%i%o%O%u%U%x%X%c%C", "bonjour", 42, &c, L"暖炉", LONG_MAX, 42, 42, 42, 100000, ULONG_MAX, 42, 42, 'c', L'플');
# endif

# ifdef UNDEFINED
	printf("\n=== UNDEFINED BEHAVIOUR ===\n");
	test_S("% 017.9S", L"ݗݜशব");
	test_S("{% S}", NULL); // ' ' => UNDEFINED
	test_S("{%+05.S}", L"42 c est cool"); // '+', '0' => UNDEFINED
	test_S("%4.2S", L"ݗݜशব");
	test_S("%-17.11S", L"ݗݜशবݜ");
	test_S("%97.35S", L"uèéeêëēėęOবशݜݗèéeêëēėęO");
	test_s("{%05p}", 0);
	test("%");
	test("%Z");
	test("% hZ");
	test_s("% Z%s", "test");
	test_s_S_p_d_D_i_o_O_u_U_x_X_c("%s %S %p %d %D %i %o %O %u %U %x %X %c", "one", L"two", str, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42);
# endif

	printf("correct tests: %i/%i\n", correct_test, total_test);
	printf("correct outputs: %i/%i\n", correct_output, total_test);
	return (0);
}

/*
** ============================================================================
** ===								TEST LOGIC								===
** ============================================================================
*/

void	compare(char *str_std, char *str_ft, int ret_std, int ret_ft, const char *format)
{
	test_count++;
	if (strcmp(str_std, str_ft))
	{
		printf("%i/%i [%s]: \x1B[31mOutput doesn't match\x1B[0m\n", test_count, total_test, format);
		printf("std: '%s'\n", str_std);
		printf("ft_: '%s'\n", str_ft);
	}
	else
	{
		printf("%i/%i [%s]: \x1B[32mOk\x1B[0m\n", test_count, total_test, format);
		correct_test++;
	}
	if (ret_ft != ret_std)
		printf("%i/%i [%s]: \x1B[33mReturn values doesn't match [std: %i, ft: %i]\x1B[0m\n", test_count, total_test, format, ret_std, ret_ft);
	else
		correct_output++;
	ft_strdel(&str_ft);
	ft_strdel(&str_std);
}

char	*to_str(int fd)
{
	char	buffer[BUFF_SIZE + 1];
	char	*str = NULL;
	char	*tmp = NULL;
	int		bcount = 1;

	str = ft_strnew(1);
	while (bcount > 0)
	{
		bcount = read(fd, buffer, BUFF_SIZE);
		buffer[bcount] = '\0';
		tmp = str;
		str = ft_strjoin(str, buffer);
		ft_strdel(&tmp);
	}
	return (str);
}

/*
** ============================================================================
** ===								COMMON TESTS							===
** ============================================================================
*/

void	test(const char *format)
{
	FILE	*fd_std = NULL;
	FILE	*fd_ft = NULL;
	char	*str_std = NULL;
	char	*str_ft = NULL;
	int		ret_std = 0;
	int		ret_ft = 0;

	fd_std = freopen(PRINTF_TEST, "w+", stdout);
	ret_std = printf(format);
	rewind(fd_std);
	str_std = to_str(fileno(fd_std));
	freopen(STD_OUT, "w", stdout);
	fd_ft = freopen(FT_TEST, "w+", stdout);
	ret_ft = ft_printf(format);
	rewind(fd_ft);
	str_ft = to_str(fileno(fd_ft));
	freopen(STD_OUT, "w", stdout);
	compare(str_std, str_ft, ret_std, ret_ft, format);
}

void	test_i(const char *format, uintmax_t nb)
{
	FILE	*fd_std = NULL;
	FILE	*fd_ft = NULL;
	char	*str_std = NULL;
	char	*str_ft = NULL;
	int		ret_std = 0;
	int		ret_ft = 0;

	fd_std = freopen(PRINTF_TEST, "w+", stdout);
	ret_std = printf(format, nb);
	rewind(fd_std);
	str_std = to_str(fileno(fd_std));
	freopen(STD_OUT, "w", stdout);
	fd_ft = freopen(FT_TEST, "w+", stdout);
	ret_ft = ft_printf(format, nb);
	rewind(fd_ft);
	str_ft = to_str(fileno(fd_ft));
	freopen(STD_OUT, "w", stdout);
	compare(str_std, str_ft, ret_std, ret_ft, format);
}

void	test_s(const char *format, const char *str)
{
	FILE	*fd_std = NULL;
	FILE	*fd_ft = NULL;
	char	*str_std = NULL;
	char	*str_ft = NULL;
	int		ret_std = 0;
	int		ret_ft = 0;

	fd_std = freopen(PRINTF_TEST, "w+", stdout);
	ret_std = printf(format, str);
	rewind(fd_std);
	str_std = to_str(fileno(fd_std));
	freopen(STD_OUT, "w", stdout);
	fd_ft = freopen(FT_TEST, "w+", stdout);
	ret_ft = ft_printf(format, str);
	rewind(fd_ft);
	str_ft = to_str(fileno(fd_ft));
	freopen(STD_OUT, "w", stdout);
	compare(str_std, str_ft, ret_std, ret_ft, format);
}

void	test_S(const char *format, const wchar_t *wstr)
{
	FILE	*fd_std = NULL;
	FILE	*fd_ft = NULL;
	char	*str_std = NULL;
	char	*str_ft = NULL;
	int		ret_std = 0;
	int		ret_ft = 0;

	fd_std = freopen(PRINTF_TEST, "w+", stdout);
	ret_std = printf(format, wstr);
	rewind(fd_std);
	str_std = to_str(fileno(fd_std));
	freopen(STD_OUT, "w", stdout);
	fd_ft = freopen(FT_TEST, "w+", stdout);
	ret_ft = ft_printf(format, wstr);
	rewind(fd_ft);
	str_ft = to_str(fileno(fd_ft));
	freopen(STD_OUT, "w", stdout);
	compare(str_std, str_ft, ret_std, ret_ft, format);
}

/*
** ============================================================================
** ===							EXOTIC TESTS								===
** ============================================================================
*/

void	test_s_s_s(const char *format, const char *s1, const char *s2, const char *s3)
{
	FILE	*fd_std = NULL;
	FILE	*fd_ft = NULL;
	char	*str_std = NULL;
	char	*str_ft = NULL;
	int		ret_std = 0;
	int		ret_ft = 0;

	fd_std = freopen(PRINTF_TEST, "w+", stdout);
	ret_std = printf(format, s1, s2, s3);
	rewind(fd_std);
	str_std = to_str(fileno(fd_std));
	freopen(STD_OUT, "w", stdout);
	fd_ft = freopen(FT_TEST, "w+", stdout);
	ret_ft = ft_printf(format, s1, s2, s3);
	rewind(fd_ft);
	str_ft = to_str(fileno(fd_ft));
	freopen(STD_OUT, "w", stdout);
	compare(str_std, str_ft, ret_std, ret_ft, format);
}

void	test_s_i_s_s(const char *format, const char *s1, int i, const char *s2, const char *s3)
{
	FILE	*fd_std = NULL;
	FILE	*fd_ft = NULL;
	char	*str_std = NULL;
	char	*str_ft = NULL;
	int		ret_std = 0;
	int		ret_ft = 0;

	fd_std = freopen(PRINTF_TEST, "w+", stdout);
	ret_std = printf(format, s1, i, s2, s3);
	rewind(fd_std);
	str_std = to_str(fileno(fd_std));
	freopen(STD_OUT, "w", stdout);
	fd_ft = freopen(FT_TEST, "w+", stdout);
	ret_ft = ft_printf(format, s1, i, s2, s3);
	rewind(fd_ft);
	str_ft = to_str(fileno(fd_ft));
	freopen(STD_OUT, "w", stdout);
	compare(str_std, str_ft, ret_std, ret_ft, format);
}

void	test_s_C_d_p_x_S(const char *format, const char *s, uintmax_t C, intmax_t d, void (*p)(void *), intmax_t x, const wchar_t *ws)
{
	FILE	*fd_std = NULL;
	FILE	*fd_ft = NULL;
	char	*str_std = NULL;
	char	*str_ft = NULL;
	int		ret_std = 0;
	int		ret_ft = 0;

	fd_std = freopen(PRINTF_TEST, "w+", stdout);
	ret_std = printf(format, s, C, d, p, x, ws);
	rewind(fd_std);
	str_std = to_str(fileno(fd_std));
	freopen(STD_OUT, "w", stdout);
	fd_ft = freopen(FT_TEST, "w+", stdout);
	ret_ft = ft_printf(format, s, C, d, p, x, ws);
	rewind(fd_ft);
	str_ft = to_str(fileno(fd_ft));
	freopen(STD_OUT, "w", stdout);
	compare(str_std, str_ft, ret_std, ret_ft, format);
}

void	test_s_S_p_d_D_i_o_O_u_U_x_X_c(const char *format, const char *str, const wchar_t *wstr, const char *ptr, int d, int D, int i, int o, int O, int u, int U, int x, int X, int c)
{
	FILE	*fd_std = NULL;
	FILE	*fd_ft = NULL;
	char	*str_std = NULL;
	char	*str_ft = NULL;
	int		ret_std = 0;
	int		ret_ft = 0;

	fd_std = freopen(PRINTF_TEST, "w+", stdout);
	ret_std = printf(format, str, wstr, ptr, d, D, i, o, O, u, U, x, X, c);
	rewind(fd_std);
	str_std = to_str(fileno(fd_std));
	freopen(STD_OUT, "w", stdout);
	fd_ft = freopen(FT_TEST, "w+", stdout);
	ret_ft = ft_printf(format, str, wstr, ptr, d, D, i, o, O, u, U, x, X, c);
	rewind(fd_ft);
	str_ft = to_str(fileno(fd_ft));
	freopen(STD_OUT, "w", stdout);
	compare(str_std, str_ft, ret_std, ret_ft, format);
}

void	test_s_d_p_S_D_i_o_O_u_U_x_X_c_C(const char *format, const char *s, intmax_t d, const char *p, const wchar_t *S, intmax_t D, intmax_t i, uintmax_t o, uintmax_t O, uintmax_t u, uintmax_t U, uintmax_t x, uintmax_t X, intmax_t c, intmax_t C)
{
	FILE	*fd_std = NULL;
	FILE	*fd_ft = NULL;
	char	*str_std = NULL;
	char	*str_ft = NULL;
	int		ret_std = 0;
	int		ret_ft = 0;

	fd_std = freopen(PRINTF_TEST, "w+", stdout);
	ret_std = printf(format, s, d, p, S, D, i, o, O, u, U, x, X, c, C);
	rewind(fd_std);
	str_std = to_str(fileno(fd_std));
	freopen(STD_OUT, "w", stdout);
	fd_ft = freopen(FT_TEST, "w+", stdout);
	ret_ft = ft_printf(format, s, d, p, S, D, i, o, O, u, U, x, X, c, C);
	rewind(fd_ft);
	str_ft = to_str(fileno(fd_ft));
	freopen(STD_OUT, "w", stdout);
	compare(str_std, str_ft, ret_std, ret_ft, format);
}

char	*_sp(char *dst, const char *src, char c)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(src);
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = c;
	dst[i + 1] = '\0';

	return (dst);
}

void	full_test(char specifier, int value)
{
	char	*str = malloc(10);

	// DEFINED

	test_i(_sp(str, "%", specifier), value);
	// WIDTH
	test_i(_sp(str, "%20", specifier), value);
	// PRECISION
	test_i(_sp(str, "%.", specifier), value);
	// +
	test_i(_sp(str, "%+", specifier), value);
	// -
	test_i(_sp(str, "%-", specifier), value);
	// ' '
	test_i(_sp(str, "% ", specifier), value);
	// 0
	test_i(_sp(str, "%0", specifier), value);

	// MIXED WIDTH
	test_i(_sp(str, "%9.6", specifier), value);

	// MIXED PRECISION
	test_i(_sp(str, "%.6", specifier), value);

	// MIXED + -
	test_i(_sp(str, "%+20", specifier), value);
	test_i(_sp(str, "%-20", specifier), value);
	test_i(_sp(str, "%+9.6", specifier), value);
	test_i(_sp(str, "%-9.6", specifier), value);
	test_i(_sp(str, "%+05", specifier), value);
	test_i(_sp(str, "%-05", specifier), value); // NOT UNDEFINED, BUT '0' IS IGNORED BECAUSE OF '-'
	test_i(_sp(str, "%+07.3", specifier), value);
	test_i(_sp(str, "%-07.3", specifier), value); // NOT UNDEFINED, BUT '0' IS IGNORED BECAUSE OF '-'

	// MIXED ' '
	test_i(_sp(str, "% 10", specifier), value);
	test_i(_sp(str, "% -10", specifier), value);
	test_i(_sp(str, "% .5", specifier), value);
	test_i(_sp(str, "% -.5", specifier), value);
	test_i(_sp(str, "% 10.5", specifier), value);
	test_i(_sp(str, "% -10.5", specifier), value);

	// MIXED 0
	test_i(_sp(str, "%05", specifier), value);
	test_i(_sp(str, "%0+5", specifier), value);
	test_i(_sp(str, "%07.2", specifier), value);

	if (specifier == 'i' || specifier == 'd' || specifier == 'D')
	{
		ft_strdel(&str);
		return;
	}

	// #
	test_i(_sp(str, "%#", specifier), value); // UNDEFINED with 'i'

	// MIXED #
	test_i(_sp(str, "%#8", specifier), value);
	test_i(_sp(str, "%#-8", specifier), value);
	test_i(_sp(str, "%#08", specifier), value);
	test_i(_sp(str, "%#-08", specifier), value);
	test_i(_sp(str, "%#.", specifier), value);
	test_i(_sp(str, "%#.0", specifier), value);
	test_i(_sp(str, "%#.3", specifier), value);
	test_i(_sp(str, "%#5.", specifier), value);
	test_i(_sp(str, "%#5.0", specifier), value);
	test_i(_sp(str, "%#5.3", specifier), value);

	// UNDEFINED
	// LENGTH
	//test_i(_sp(str, "%hh", specifier), value); // UNDEFINED, not same type as value

	ft_strdel(&str);
}
