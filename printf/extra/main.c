#include <stdio.h>
#include <libft.h>

#define EXPLICIT
//#define SPECIFIERS
#define FLAGS

int main(void)
{
	wchar_t	*wstr = L"a sample wide string";
	char	*str = "a sample string";
	int		nb = 42;

	(void)wstr;
	(void)str;
	(void)nb;
	// sS  string of characters
	// p   pointer adresse
	// dD  signed decimal integer
	// i   signed decimal integer
	// oO  unsigned octal
	// uU  unsigned decimal integer
	// xX  unsigned hexadecimal integer lowercase / uppercase
	// cC  character

#ifdef EXPLICIT

# ifdef SPECIFIERS

	ft_putendl("Specifier: %%");
	printf("std: %%\n");
	ft_printf("ft_: %%\n");
	ft_putstr("\n");

	ft_putendl("Specifier: %s %S");
	printf("std: %s\n", str);
	ft_printf("ft_: %s\n", str);
	printf("std: %s\n", "a constant string");
	ft_printf("ft_: %s\n", "a constant string");
	printf("std: %S\n", wstr);
	printf("std: %S\n", L"a constant wide string");
	//ft_printf("ft_: %%\n");
	ft_putstr("\n");

	ft_putendl("Specifier: %p");
	printf("std: %p\n", str);
	printf("std: %p\n", "constant");
	ft_printf("ft_: %p\n", str);
	ft_printf("ft_: %p\n", "constant");
	ft_putstr("\n");

	ft_putendl("Specifier: %d %D");
	printf("std: %d\n", nb);
	ft_printf("ft_: %d\n", nb);
	printf("std: %D\n", nb);
	ft_putstr("\n");

	ft_putendl("Specifier: %i");
	printf("std: %i\n", nb);
	ft_printf("ft_: %i\n", nb);
	ft_putstr("\n");

	ft_putendl("Specifier: %o %O");
	printf("std: %o\n", nb);
	ft_printf("ft_: %o\n", nb);
	printf("std: %O\n", nb);
	ft_putstr("\n");

	ft_putendl("Specifier: %u %U");
	printf("std: %u\n", nb);
	ft_printf("ft_: %u\n", nb);
	printf("std: %U\n", nb);
	ft_putstr("\n");

	ft_putendl("Specifier: %x %X");
	printf("std: %x\n", nb);
	ft_printf("ft_: %x\n", nb);
	printf("std: %X\n", nb);
	ft_putstr("\n");

	ft_putendl("Specifier: %c");
	printf("std: %c\n", nb);
	ft_printf("ft_: %c\n", nb);
	ft_putstr("\n");
# endif
# ifdef FLAGS
	ft_putendl("Flag: -");
	printf("std: %-i\n", nb);
	//ft_printf("ft_: %-i\n", nb);
	ft_putstr("\n");

	ft_putendl("Flag: +");
	ft_putendl("Specifier: %d %D");
	printf("std: %+d\n", nb);
	ft_printf("ft_: %+d\n", nb);
	ft_putendl("Specifier: %i");
	printf("std: %-+i\n", nb);
	ft_printf("ft_: %-+i\n", nb);
	ft_putstr("\n");

	ft_putendl("Flag: {space}");
	printf("std: %    i\n", nb);
	ft_printf("ft_: %    i\n", nb);
# endif
#else

	// sS  string of characters
	// p   pointer adresse
	// dD  signed decimal integer
	// i   signed decimal integer
	// oO  unsigned octal
	// uU  unsigned decimal integer
	// xX  unsigned hexadecimal integer lowercase / uppercase
	// cC  character
	printf("Hello\n");
	ft_printf("Hello\n");

#endif

	return (0);
}
