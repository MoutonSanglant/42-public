#include <stdio.h>
#include <libft.h>

#define EXPLICIT
//#define SPECIFIERS
//#define FLAGS
//#define WIDTH
#define PRECISION

int main(void)
{
	wchar_t	*wstr = L"a sample wide string";
	char	*str = "a sample string";
	int		nb = 42;

	(void)wstr;
	(void)str;
	(void)nb;
	// sS  string of characters
	// p   pointer address
	// dD  signed decimal integer
	// i   signed decimal integer
	// oO  unsigned octal
	// uU  unsigned decimal integer
	// xX  unsigned hexadecimal integer lowercase / uppercase
	// cC  character

#ifdef EXPLICIT

# ifdef SPECIFIERS

	ft_putendl("Specifier: %%");
	printf(" (%i)\n", printf("std: %%"));
	printf(" (%i)\n", ft_printf("ft_: %%"));
	printf(" (%i)\n", printf("std: %%i"));
	printf(" (%i)\n", ft_printf("ft_: %%i"));
	printf(" (%i)\n", printf("std: %% is a percent symbol"));
	printf(" (%i)\n", ft_printf("ft_: %% is a percent symbol"));
	ft_putstr("\n");

	ft_putendl("Specifier: %s %S");
	printf(" (%i)\n", printf("std: %s", str));
	printf(" (%i)\n", ft_printf("ft_: %s", str));
	printf(" (%i)\n", printf("std: %s", "a constant string"));
	printf(" (%i)\n", ft_printf("ft_: %s", "a constant string"));
	printf(" (%i)\n", printf("std: %S", wstr));
	printf(" (%i)\n", printf("std: %S", L"a constant wide string"));
	printf(" (%i)\n", printf("std: %s", NULL));
	printf(" (%i)\n", ft_printf("ft_: %s", NULL));
	//ft_printf("ft_: %%\n");
	ft_putstr("\n");

	ft_putendl("Specifier: %p");
	printf(" (%i)\n", printf("std: %p", str));
	printf(" (%i)\n", printf("std: %p", "constant"));
	printf(" (%i)\n", ft_printf("ft_: %p", str));
	printf(" (%i)\n", ft_printf("ft_: %p", "constant"));
	printf(" (%i)\n", printf("std: %p", NULL));
	printf(" (%i)\n", ft_printf("ft_: %p", NULL));
	ft_putstr("\n");

	ft_putendl("Specifier: %d %D");
	printf(" (%i)\n", printf("std: %d", nb));
	printf(" (%i)\n", ft_printf("ft_: %d", nb));
	printf(" (%i)\n", printf("std: %D", nb));
	ft_putstr("\n");

	ft_putendl("Specifier: %i");
	printf(" (%i)\n", printf("std: %i", nb));
	printf(" (%i)\n", ft_printf("ft_: %i", nb));
	printf(" (%i)\n", printf("std: %i is an int", nb));
	printf(" (%i)\n", ft_printf("ft_: %i is an int", nb));
	ft_putstr("\n");

	ft_putendl("Specifier: %o %O");
	printf(" (%i)\n", printf("std: %o", nb));
	printf(" (%i)\n", ft_printf("ft_: %o", nb));
	printf(" (%i)\n", printf("std: %O", nb));
	ft_putstr("\n");

	ft_putendl("Specifier: %u %U");
	printf(" (%i)\n", printf("std: %u", nb));
	printf(" (%i)\n", ft_printf("ft_: %u", nb));
	printf(" (%i)\n", printf("std: %U", nb));
	ft_putstr("\n");

	ft_putendl("Specifier: %x %X");
	printf(" (%i)\n", printf("std: %x", nb));
	printf(" (%i)\n", ft_printf("ft_: %x", nb));
	printf(" (%i)\n", printf("std: %X", nb));
	ft_putstr("\n");

	ft_putendl("Specifier: %c");
	printf(" (%i)\n", printf("std: %c", nb));
	printf(" (%i)\n", ft_printf("ft_: %c", nb));
	ft_putstr("\n");
# endif
# ifdef FLAGS
	ft_putendl("Flag: -");
	printf(" (%i)\n", printf("std: %-i", nb));
	//ft_printf("ft_: %-i\n", nb);
	ft_putstr("\n");

	ft_putendl("Flag: +");
	ft_putendl("Specifier: %d %D");
	printf(" (%i)\n", printf("std: %+d", nb));
	printf(" (%i)\n", ft_printf("ft_: %+d", nb));
	ft_putendl("Specifier: %i");
	printf(" (%i)\n", printf("std: %-+-+d", nb));
	printf(" (%i)\n", ft_printf("ft_: %-+-+d", nb));
	ft_putstr("\n");

	ft_putendl("Flag: {space}");
	printf(" (%i)\n", printf("std: % i", nb));
	printf(" (%i)\n", ft_printf("ft_: % i", nb));
#endif
#ifdef WIDTH
	ft_putendl("Width: printf(\"%5i\", 42)");
	printf(" (%i)\n", printf("std: %5i", 42));
	printf(" (%i)\n", ft_printf("ft_: %5i", 42 ));
	ft_putstr("\n");
# endif
#ifdef PRECISION
	ft_putendl("Precision: printf(\"%.5i\", 42)");
	printf(" (%i)\n", printf("std: %-9.15i", 42));
	printf(" (%i)\n", ft_printf("ft_: %-9.15i", 42 ));
	ft_putstr("\n");
# endif
#else

	// sS  string of characters
	// p   pointer address
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
