#include <stdio.h>
#include <libft.h>

#include <locale.h>

#define SPECIFIERS
#define MULTI_SPEC
#define FLAGS
#define WIDTH
#define PRECISION
#define LENGTH
#define MISSING
#define HEX
#define OCT

#define CHAR
#define DIGIT
#define UNSIGNED
#define NOSPEC
#define UNSPEC
#define HARDCORE
#define MOULITEST

#define PRINTF_TEST "printf_out.tmp"
#define FT_TEST "ft_out.tmp"
#define STD_OUT "/dev/tty"
#define BUFF_SIZE 1024

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

void	compare(char *str_std, char *str_ft, int ret_std, int ret_ft, const char *format)
{
	if (ft_strcmp(str_std, str_ft))
	{
		printf("[%s]: \x1B[31mOutput doesn't match\x1B[0m\n", format);
		printf("std: %s\n", str_std);
		printf("ft_: %s\n", str_ft);
	}
	else if (ret_ft != ret_std)
		printf("[%s]: \x1B[33mReturn values doesn't match [std: %i, ft: %i]\x1B[0m\n", format, ret_std, ret_ft);
	else
		printf("[%s]: \x1B[32mOk\x1B[0m\n", format);
	ft_strdel(&str_ft);
	ft_strdel(&str_std);
}

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

	(void)wstr;
	(void)str;
	(void)nb;
	(void)i;
	(void)l;
	(void)ll;
	(void)im;
	(void)c;

	setlocale(LC_ALL, "fr_FR.UTF-8");

# ifdef SPECIFIERS

	ft_putendl("=== SPECIFIERS ===");
	test("%%");
	//ft_putendl("=== %s ===");
	test_s("%s", str);
	test_s("%s", "a constant string");
	test_s("%s", NULL);
	//ft_putendl("=== %S ===");
	test_S("%S", wstr);
	test_S("%S", L"a constant wide string");
	test_S("%S", NULL);
	//ft_putendl("=== %p ===");
	test_s("%p", str);
	test_s("%p", "constant");
	test_s("%p", NULL);
	//ft_putendl("=== %d ===");
	test_i("%d", nb);
	//ft_putendl("=== %D ===");
	test_i("%D", nb);
	//ft_putendl("=== %i ===");
	test_i("%i", nb);
	//ft_putendl("=== %o ===");
	test_i("%o", nb);
	//ft_putendl("=== %O ===");
	test_i("%O", nb);
	//ft_putendl("=== %u ===");
	test_i("%u", nb);
	//ft_putendl("=== %U ===");
	test_i("%U", nb);
	//ft_putendl("=== %x ===");
	test_i("%x", nb);
	//ft_putendl("=== %X ===");
	test_i("%X", nb);
	//ft_putendl("=== %c ===");
	test_i("%c", nb);
# endif

# ifdef BASIC
	ft_putendl("\n=== BASIC ===");
	test("%%i");
	test("%% is a percent symbol");
	test_i("%i is an int", nb);
	test_s("%s", "une chaine avec 'éç' dedans");
# endif

# ifdef MULTI_SPEC
	ft_putendl("\n=== MULTIPLE SPECIFIERS ===");
	test_s_s_s("%s %s %s", "one", "two", "three");
	test_s_S_p_d_D_i_o_O_u_U_x_X_c("%s %S %p %d %D %i %o %O %u %U %x %X %c", "one", L"two", str, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42);
# endif

# ifdef FLAGS
	ft_putendl("\n=== FLAGS ===");
	test_i("%-i", nb);
	test_i("%+i", nb);
	test_i("% i", nb);
	test_i("%+d", nb);
	test_i("%-+-+d", nb);
	test_i("%#x", 42);
	test_i("%#X", 42);
	test_i("%#o", 42);
	test_s("%-10s is a string", "this");
	test_s("%-2.s is a string", "this");
	test_s("%#-2.s is a string", "this");
	test_s("%-10s is a string", "");
	test_s("%#-10s is a string", "");
	test_s("%-5.2s is a string", "");
	test_s("%#-5.2s is a string", "");
# endif

# ifdef WIDTH
	ft_putendl("\n=== WIDTH ===");
	test_i("%5i", 42);
	test_s("%10s", "this");
	test_s("%0s", "this");
# endif

# ifdef PRECISION
	ft_putendl("\n=== PRECISION ===");
	test_i("%.5i", 42);
	test_i("%.5i", -42);
	test_i("% .5i", 42);
	test_i("% .5i", -42);
	test_s("%.2s is a string", "this");
	test_s("%5.2s is a string", "this");
	test_s("%5.0s is a string", "this");
# endif

# ifdef LENGTH
	ft_putendl("\n=== LENGTH ===");
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
	ft_putendl("\n=== MISSING SPECIFIER ===");
	test("");
	test("%%");
	test("%5%");
	test("%-5%");
	test("%   %");
	test("%+%");
	test("% .3% Hello ! %% % .3%");
# endif

# ifdef HEX
	ft_putendl("\n=== HEXADECIMAL ===");
	test_i("%10x", 42);
	test_i("%10X", 42);
	test_i("%-10x", 42);
	test_i("%-10X", 42);
	test_i("%#x", 42);
	test_i("%#X", 42);
	test_i("%#8x", 42);
	test_i("%#8X", 42);
	test_i("%#-8x", 42);
	test_i("%#-8X", 42);
	test_i("%#08x", 42);
	test_i("%#08X", 42);
	test_i("%#-08x", 42);
	test_i("%#-08X", 42);
	test_i("%#x", 0);
	test_i("%#X", 0);
	test_i("%#.x", 0);
	test_i("%#.X", 0);
	test_i("%#.0x", 0);
	test_i("%#.0X", 0);
	test_i("%#5.x", 0);
	test_i("%#5.X", 0);
	test_i("%#5.0x", 0);
	test_i("%#5.0X", 0);
# endif

# ifdef OCT
	ft_putendl("\n=== OCTAL ===");
	test_i("%10o", 42);
	test_i("%10O", 42);
	test_i("%-10o", 42);
	test_i("%-10O", 42);
	test_i("%#o", 42);
	test_i("%#O", 42);
	test_i("%#8o", 42);
	test_i("%#8O", 42);
	test_i("%#-8o", 42);
	test_i("%#-8O", 42);
	test_i("%#08o", 42);
	test_i("%#08O", 42);
	test_i("%#-08o", 42);
	test_i("%#-08O", 42);
	test_i("%#o", 0);
	test_i("%#O", 0);
	test_i("%#.o", 0);
	test_i("%#.O", 0);
	test_i("%#.0o", 0);
	test_i("%#.0O", 0);
	test_i("%#5.o", 0);
	test_i("%#5.O", 0);
	test_i("%#5.0o", 0);
	test_i("%#5.0O", 0);
# endif

# ifdef UNSIGNED
	ft_putendl("\n=== UNSIGNED ===");
	test_i("%10u", 42);
	test_i("%10U", 42);
	test_i("%-10u", 42);
	test_i("%-10U", 42);
	test_i("%#u", 42);
	test_i("%#U", 42);
	test_i("%#8u", 42);
	test_i("%#8U", 42);
	test_i("%#-8u", 42);
	test_i("%#-8U", 42);
	test_i("%#08u", 42);
	test_i("%#08U", 42);
	test_i("%#-08u", 42);
	test_i("%#-08U", 42);
	test_i("%#u", 0);
	test_i("%#U", 0);
	test_i("%#.u", 0);
	test_i("%#.U", 0);
	test_i("%#.0u", 0);
	test_i("%#.0U", 0);
	test_i("%#5.u", 0);
	test_i("%#5.U", 0);
	test_i("%#5.0u", 0);
	test_i("%#5.0U", 0);
	test_i("%5u", -42);
	test_i("%+5u", 42);
	test_i("%0+5u", 42);
	test_i("%0+5u", -42);
	test_i("%05u", -42);
	test_i("%-05u", 42);
	test_i("%-05u", -42);
	test_i("%-5u", -42);
	test_i("%-9.6u", 4242);
	test_i("%9.6u", 4242);
	test_i("%.6u", -4242);
	test_i("% 10.5u", 4242);
	test_i("%- 10.5u", 4242);
	test_i("%07.2u", 0);
	test_i("%-07.3u", -42);
	test_i("%-7.4u", -42);
	test_i("%u", -1);
	test_i("% u", -1);
# endif

# ifdef CHAR
	ft_putendl("\n=== CHAR ===");
	test_i("%10c", 42);
	test_i("%10C", 42);
	test_i("%-10c", 42);
	test_i("%-10C", 42);
	test_i("%#c", 42);
	test_i("%#C", 42);
	test_i("%#8c", 42);
	test_i("%#8C", 42);
	test_i("%#-8c", 42);
	test_i("%#-8C", 42);
	test_i("%#08c", 42);
	test_i("%#08C", 42);
	test_i("%#-08c", 42);
	test_i("%#-08C", 42);
	test_i("%#c", 0);
	test_i("%#C", 0);
	test_i("%#.c", 0);
	test_i("%#.C", 0);
	test_i("%#.0c", 0);
	test_i("%#.0C", 0);
	test_i("%#5.c", 0);
	test_i("%#5.C", 0);
	test_i("%#5.0c", 0);
	test_i("%#5.0C", 0);
	test_i("%5c", -42);
	test_i("%5C", -42);

	test_i("%+5c", 42);
	test_i("%+5C", 42);
	test_i("%0+5c", 42);
	test_i("%0+5C", 42);
	test_i("%0+5c", -42);
	test_i("%0+5C", -42);
	test_i("%05c", -42);
	test_i("%05C", -42);
	test_i("%-05c", 42);
	test_i("%-05C", 42);
	test_i("%-05c", -42);
	test_i("%-05C", -42);
	test_i("%-5c", -42);
	test_i("%-5C", -42);
	test_i("%-9.6c", 4242);
	test_i("%-9.6C", 4242);
	test_i("%9.6c", 4242);
	test_i("%9.6C", 4242);
	test_i("%.6c", -4242);
	test_i("%.6C", -4242);
	test_i("% 10.5c", 4242);
	test_i("% 10.5C", 4242);
	test_i("%- 10.5c", 4242);
	test_i("%- 10.5C", 4242);
	test_i("%07.2c", 0);
	test_i("%07.2C", 0);
	test_i("%-07.3c", -42);
	test_i("%-07.3C", -42);
	test_i("%-7.4c", -42);
	test_i("%-7.4C", -42);
	test_i("%c", -1);
	test_i("%C", -1);
	test_i("% c", -1);
	test_i("% C", -1);
	test_i("%# c", 42);
	test_i("%# C", 42);
	test_i("%# .3c", 42);
	test_i("%# .3C", 42);
	test_i("%.2c", 0);
	test_i("%.2C", 0);
	test_i("%#.2c", 0);
	test_i("%#.2C", 0);
# endif

# ifdef DIGIT
	ft_putendl("\n=== DIGIT ===");
	test_i("%10d", 42);
	test_i("%10D", 42);
	test_i("%-10d", 42);
	test_i("%-10D", 42);
	test_i("%#d", 42);
	test_i("%#D", 42);
	test_i("%#8d", 42);
	test_i("%#8D", 42);
	test_i("%#-8d", 42);
	test_i("%#-8D", 42);
	test_i("%#08d", 42);
	test_i("%#08D", 42);
	test_i("%#-08d", 42);
	test_i("%#-08D", 42);
	test_i("%#d", 0);
	test_i("%#D", 0);
	test_i("%#.d", 0);
	test_i("%#.D", 0);
	test_i("%#.0d", 0);
	test_i("%#.0D", 0);
	test_i("%#5.d", 0);
	test_i("%#5.D", 0);
	test_i("%#5.0d", 0);
	test_i("%#5.0D", 0);
	test_i("%5d", -42);
	test_i("%5D", -42);
	test_i("%+5d", 42);
	test_i("%+5D", 42);
	test_i("%0+5d", 42);
	test_i("%0+5D", 42);
	test_i("%0+5d", -42);
	test_i("%0+5D", -42);
	test_i("%05d", -42);
	test_i("%05D", -42);
	test_i("%-05d", 42);
	test_i("%-05D", 42);
	test_i("%-05d", -42);
	test_i("%-05D", -42);
	test_i("%-5d", -42);
	test_i("%-5D", -42);
	test_i("%-9.6d", 4242);
	test_i("%-9.6D", 4242);
	test_i("%9.6d", 4242);
	test_i("%9.6D", 4242);
	test_i("%.6d", -4242);
	test_i("%.6D", -4242);
	test_i("% 10.5d", 4242);
	test_i("% 10.5D", 4242);
	test_i("%- 10.5d", 4242);
	test_i("%- 10.5D", 4242);
	test_i("%07.2d", 0);
	test_i("%07.2D", 0);
	test_i("%-07.3d", -42);
	test_i("%-07.3D", -42);
	test_i("%-7.4d", -42);
	test_i("%-7.4D", -42);
	test_i("%d", -1);
	test_i("%D", -1);
	test_i("% d", -1);
	test_i("% D", -1);
	test_i("%# d", 42);
	test_i("%# D", 42);
	test_i("%# .3d", 42);
	test_i("%# .3D", 42);
	test_i("%.2d", 0);
	test_i("%.2D", 0);
	test_i("%#.2d", 0);
	test_i("%#.2D", 0);

	test_i("%10i", 42);
	test_i("%-10i", 42);
	test_i("%#i", 42);
	test_i("%#8i", 42);
	test_i("%#-8i", 42);
	test_i("%#08i", 42);
	test_i("%#-08i", 42);
	test_i("%#i", 0);
	test_i("%#.i", 0);
	test_i("%#.0i", 0);
	test_i("%#5.i", 0);
	test_i("%#5.0i", 0);
	test_i("%5i", -42);
	test_i("%+5i", 42);
	test_i("%0+5i", 42);
	test_i("%0+5i", -42);
	test_i("%05i", -42);
	test_i("%-05i", 42);
	test_i("%-05i", -42);
	test_i("%-5i", -42);
	test_i("%-9.6i", 4242);
	test_i("%9.6i", 4242);
	test_i("%.6i", -4242);
	test_i("% 10.5i", 4242);
	test_i("%- 10.5i", 4242);
	test_i("%07.2i", 0);
	test_i("%-07.3i", -42);
	test_i("%-7.4i", -42);
	test_i("%i", -1);
	test_i("% i", -1);
	test_i("%# i", 42);
	test_i("%# .3i", 42);
	test_i("%.2i", 0);
	test_i("%#.2i", 0);
# endif

# ifdef UNSPEC
	ft_putendl("\n=== UNSPECIFIED ===");
	test("%");
	test("%Z");
	test("% hZ");
	test_s("% Z%s", "test");
# endif

# ifdef HARDCORE
	ft_putendl("\n=== HARDCORE ===");
	test_i("%jx", -4294967296);
	test_i("%jx", -4294967297);
	test_i("%010x", 542);
	test_i("%08x", 42);
	test_i("%hhd", 128);
	test_i("%hhd", -129);
	test_i("%zhd", 4294967296);
	test_i("%jhd", 9223372036854775807);
	test("\n");
	test("%%\n");
	test_i("%d\n", 42);
	test_i("%ld\n", l);
	test_i("%lld\n", ll);
	//printf("%x %X %p %20.15d\n", 505, 505, &ll, 54321);
	//printf("%-10d % d %+d %010d %hhd\n", 3, 3, 3, 1, c);
	//printf("%jd %zd %u %o %#08x\n", im, (size_t)i, i, 40, 42);
	//printf(" (%i)\n", printf("%x %#X %S %s%s", 1000, 1000, L"ݗݜशব", "test", "test2"));
	//printf(" (%i)\n", printf("%s%s%s", "test", "test", "test"));
	test_i("%c", 75);
	test_i("%C", 8000);
	test_i("%C", 80000);
	test_i("%C", L'α');
	//printf(" (%i)\n", printf("%s, %s", "Hello les cocos !", NULL));
	//printf(" (%i)\n", ft_printf("%s, %s", "Hello les cocos !", NULL));
	//printf(" (%i)\n", printf("%-11.3s, %-11.6s", "Hello les cocos !", NULL));
	//printf(" (%i)\n", ft_printf("%-11.3s, %-11.6s", "Hello les cocos !", NULL));
	//printf(" (%i)\n", printf("%-11.3s, %-11.0s", "Hello les cocos !", NULL));
	//printf(" (%i)\n", ft_printf("%-11.3s, %-11.0s", "Hello les cocos !", NULL));
	//printf(" (%i)\n", printf("%-3.11s, %-3.11s", "Hello les cocos !", NULL));
	//printf(" (%i)\n", ft_printf("%-3.11s, %-3.11s", "Hello les cocos !", NULL));
	//printf(" (%i)\n", printf("%-s, %-s", "Hello les cocos !", NULL));
	//printf(" (%i)\n", ft_printf("%-s, %-s", "Hello les cocos !", NULL));
	//printf(" (%i)\n", printf("%4C%4C%4C%4C", L'ݗ', L'ݜ', L'श', L'ব'));
	//printf(" (%i)\n", printf("%x %#X %-17S %s%s", 1000, 1000, L"ݗݜशবݜ", "test", "test2"));
	//printf(" (%i)\n", printf("%x %#X %-17S %s%s", 1000, 1000, L"বशݜݗ", "test", "test2"));
	//printf(" (%i)\n", printf("%x %#X % 017.9S %s%s", 1000, 1000, L"ݗݜशব", "test", "test2"));
	//printf(" (%i)\n", printf("%x %#X %4.2S %s%s", 1000, 1000, L"ݗݜशব", "test", "test2"));
	//printf(" (%i)\n", printf("%x %#X %-17.11S %s%s", 1000, 1000, L"ݗݜशবݜ", "test", "test2"));
	//printf(" (%i)\n", printf("%x %#X %97.35S %s%s", 1000, 1000, L"uèéeêëēėęOবशݜݗèéeêëēėęO", "test", "test2"));

# endif
	return (0);



# ifdef HARDCORE

	
# endif
# ifdef MOULITEST
	setlocale(LC_ALL, "fr_FR.UTF-8");
	printf("1- %.c\n", 0);
	fflush(stdout);
	ft_printf("1- %.c\n", 0);
	printf("2- %.5c\n", 0);
	fflush(stdout);
	ft_printf("2- %.5c\n", 0);
	printf("3- %.5c\n", 42);
	fflush(stdout);
	ft_printf("3- %.5c\n", 42);
	printf("4- %.C\n", 0);
	fflush(stdout);
	ft_printf("4- %.C\n", 0);
	printf("5- %.5C\n", 0);
	fflush(stdout);
	ft_printf("5- %.5C\n", 0);
	printf("6- %.5C\n", 42);
	fflush(stdout);
	ft_printf("6- %.5C\n", 42);
	ft_printf("============\n");
	printf("7- {%5p}\n",  0);
	fflush(stdout);
	ft_printf("7- {%5p}\n", 0);
	printf("8- {%-15p}\n", 0);
	fflush(stdout);
	ft_printf("8- {%-15p}\n", 0);
	printf("9- {%10RN}\n");
	fflush(stdout);
	ft_printf("9- {%10RN}\n");
	printf( " (%i)\n", printf("10- {%30S}", L"我是一只猫。"));
	fflush(stdout);
	printf( " (%i)\n", ft_printf("10- {%30S}", L"我是一只猫。"));
	fflush(stdout);
	printf( " (%i)\n", printf("11- {%-30S}", L"我是一只猫。"));
	fflush(stdout);
	printf( " (%i)\n", ft_printf("11- {%-30S}", L"我是一只猫。"));
	fflush(stdout);
	ft_printf("============\n");
	printf( " (%i)\n", printf("1- %.0p, %.p", 0, 0));
	fflush(stdout);
	printf( " (%i)\n", ft_printf("1- %.0p, %.p", 0, 0));
	fflush(stdout);
	printf( " (%i)\n", printf("2- %.5p", 0));
	fflush(stdout);
	printf( " (%i)\n", ft_printf("2- %.5p", 0));
	fflush(stdout);
	printf( " (%i)\n", printf("3- %9.2p", 1234));
	fflush(stdout);
	printf( " (%i)\n", ft_printf("3- %9.2p", 1234));
	fflush(stdout);
	printf( " (%i)\n", printf("4- %9.2p", 1234567));
	fflush(stdout);
	printf( " (%i)\n", ft_printf("4- %9.2p", 1234567));
	fflush(stdout);
	printf( " (%i)\n", printf("5- %2.9p", 1234));
	fflush(stdout);
	printf( " (%i)\n", ft_printf("5- %2.9p", 1234));
	fflush(stdout);
	printf( " (%i)\n", printf("6- %2.9p", 1234567));
	fflush(stdout);
	printf( " (%i)\n", ft_printf("6- %2.9p", 1234567));
	fflush(stdout);
	ft_printf("============\n");
	printf("Haha: % s %C, % s, % s, ok.\n", "hello", L'該', NULL, "");
	ft_printf("Haha: % s %C, % s, % s, ok.\n", "hello", L'該', NULL, "");
	printf( " (%i)\n", printf("%s %C %d %p %x %% %S", "bonjour ", L'該', 42, &free, 42, L"لحم خنزير"));
	fflush(stdout);
	printf( " (%i)\n", ft_printf("%s %C %d %p %x %% %S", "bonjour ", L'該', 42, &free, 42, L"لحم خنزير"));
	/*
	char c;
	fflush(stdout);
	printf( " (%i)\n", printf("%s%d%p%%%S%D%i%o%O%u%U%x%X%c%C","bonjour", 42, &c, L"暖炉", LONG_MAX, 42, 42, 42, 100000, ULONG_MAX, 42, 42, 'c', L'플'));
	fflush(stdout);
	printf( " (%i)\n", ft_printf("%s%d%p%%%S%D%i%o%O%u%U%x%X%c%C", "bonjour", 42, &c, L"暖炉", LONG_MAX, 42, 42, 42, 100000, ULONG_MAX, 42, 42, 'c', L'플'));
	fflush(stdout);
	*/
	printf( " (%i)\n", printf("% p|%+p", 42, 42));
	fflush(stdout);
	printf( " (%i)\n", ft_printf("% p|%+p", 42, 42));
	fflush(stdout);
	printf(" (%i)\n", printf("{% s}", NULL));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("{% s}", NULL));
	fflush(stdout);
	printf(" (%i)\n", printf("{% s}", "(null)"));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("{% s}", "(null)"));
	fflush(stdout);
	printf(" (%i)\n", printf("{% s}", ""));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("{% s}", ""));
	fflush(stdout);
	printf(" (%i)\n", printf("{% S}", NULL));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("{% S}", NULL));
	fflush(stdout);
	printf(" (%i)\n", printf("%#.3o", 1));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("%#.3o", 1));
	fflush(stdout);
	printf(" (%i)\n", printf("{%+05.S}", L"42 c est cool"));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("{%+05.S}", L"42 c est cool"));
	fflush(stdout);

	printf(" (%i)\n", printf("%+o", 0));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("%+o", 0));
	fflush(stdout);
	printf(" (%i)\n", printf("%+o", 42));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("%+o", 42));
	fflush(stdout);
	printf(" (%i)\n", printf("%+O", 0));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("%+O", 0));
	fflush(stdout);
	printf(" (%i)\n", printf("%+O", 42));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("%+O", 42));
	fflush(stdout);
	printf(" (%i)\n", printf("[%+s]", 0));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("[%+s]", 0));
	fflush(stdout);
	printf(" (%i)\n", printf("[%+s]", "(null)"));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("[%+s]", "(null)"));
	fflush(stdout);
	printf(" (%i)\n", printf("%+O", 1));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("%+O", 1));
	fflush(stdout);
	printf(" (%i)\n", printf("%hhx, %hhx", 0, UCHAR_MAX + 42));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("%hhx, %hhx", 0, UCHAR_MAX + 42));
	fflush(stdout);
	printf(" (%i)\n", printf("%hhX, %hhX", 0, UCHAR_MAX + 42));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("%hhX, %hhX", 0, UCHAR_MAX + 42));
	fflush(stdout);
	printf(" (%i)\n", printf("% o|%+o", 42, 42));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("% o|%+o", 42, 42));
	fflush(stdout);
	printf(" (%i)\n", printf("% x|%+x", 42, 42));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("% x|%+x", 42, 42));
	fflush(stdout);
	printf(" (%i)\n", printf("% X|%+X", 42, 42));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("% X|%+X", 42, 42));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("% o|%+o", 42, 42));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("% o|%+o", 42, 42));
	fflush(stdout);
	printf(" (%i)\n", printf("{%05p}", 0));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("{%05p}", 0));
	fflush(stdout);
	printf(" (%i)\n", printf("{%5p}", 0));
	fflush(stdout);
	printf(" (%i)\n", ft_printf("{%5p}", 0));
	fflush(stdout);
# endif

	// sS  string of characters
	// p   pointer address
	// dD  signed decimal integer
	// i   signed decimal integer
	// oO  unsigned octal
	// uU  unsigned decimal integer
	// xX  unsigned hexadecimal integer lowercase / uppercase
	// cC  character

	return (0);
}
