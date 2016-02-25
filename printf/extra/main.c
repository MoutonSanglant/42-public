#include <stdio.h>
#include <libft.h>

#define EXPLICIT
//#define SPECIFIERS
//#define FLAGS
//#define WIDTH
//#define PRECISION
//#define LENGTH
//#define UNICODE
//#define HEX
//#define OCTAL
//#define UNSIGNED
//#define CHAR
#define DIGIT
//#define NOSPEC

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

	//printf("itoa: %i\nft_itoa: %i\n", itoa(44200), ft_itoa(44200));
	/*
	printf("intmax_t: %i\n", sizeof(intmax_t));
	printf("int64_t: %i\n", sizeof(int64_t));
	printf("int: %i\n", sizeof(int));
	printf("long int: %i\n", sizeof(long int));
	printf("long long int: %i\n", sizeof(long long int));
	*/

#ifdef EXPLICIT

# ifdef SPECIFIERS

	ft_putendl("Specifier: %%");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%%"));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%%"));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%%i"));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%%i"));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%% is a percent symbol"));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%% is a percent symbol"));
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
	printf(" (%i)\n", ft_printf("ft_: %p", str));
	printf(" (%i)\n", printf("std: %p", "constant"));
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
	ft_putstr("std:");
	printf(" (%i)\n", printf("%+d", nb));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%+d", nb));
	ft_putendl("Specifier: %i");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-+-+d", nb));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%-+-+d", nb));
	ft_putstr("\n");
	ft_putendl("Flag: {space}");
	ft_putstr("std:");
	printf(" (%i)\n", printf("% i", nb));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("% i", nb));
	ft_putstr("\n");
	ft_putendl("Flag: #");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#x", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#x", 42));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#X", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#X", 42));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#o", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#o", 42));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-10s is a string", "this"));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#-10s is a string", "this"));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-.2s is a string", "this"));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#-.2s is a string", "this"));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-10s is a string", ""));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#-10s is a string", ""));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-5.2s is a string", ""));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#-5.2s is a string", ""));
# endif
# ifdef WIDTH
	ft_putendl("Width: printf(\"%5i\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%5i", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%5i", 42 ));
	ft_putstr("\n");
	ft_putendl("printf(\"%10s\" is a string, \"this\")");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%10s is a string", "this"));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%10s is a string", "this"));
	ft_putstr("\n");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%0s is a string", "this"));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%0s is a string", "this"));
	ft_putstr("\n");
# endif
# ifdef PRECISION
	ft_putendl("Precision: printf(\"%.5i\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%.5i", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%.5i", 42));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%.5i", -42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%.5i", -42));
	ft_putstr("std:");
	printf(" (%i)\n", printf("% .5i", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("% .5i", 42));
	ft_putstr("std:");
	printf(" (%i)\n", printf("% .5i", -42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("% .5i", -42));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%.2s is a string", "this"));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%.2s is a string", "this"));
	ft_putstr("\n");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%5.2s is a string", "this"));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%5.2s is a string", "this"));
	ft_putstr("\n");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%5.0s is a string", "this"));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%5.0s is a string", "this"));
	ft_putstr("\n");
# endif
# ifdef LENGTH
	ft_putendl("Length: printf(\"%hi\", 44200)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%hi", 44200));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%hi", 44200));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%hhi", 44200));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%hhi", 44200));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%i", 2147483650));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%i", 2147483650));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%li", 2147483650));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%li", 2147483650));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%lli", 9223372036854775807));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%lli", 9223372036854775807));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%ji", 9223372036854775807));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%ji", 9223372036854775807));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%zi", 9223372036854775807));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%zi", 9223372036854775807));
	ft_putstr("std:");
	printf(" (%i)\n", printf("%i", 9223372036854775807));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%i", 9223372036854775807));
	ft_putstr("\n");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#llx", 9223372036854775807));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#llx", 9223372036854775807));
# endif
# ifdef UNICODE
	ft_putendl("Width: printf(\"éç\")");
	printf(" (%i)\n", printf("std: éç"));
	printf(" (%i)\n", ft_printf("ft_: éç"));
	ft_putstr("\n");
# endif
# ifdef NOSPEC
	ft_putendl("printf(\"\")");
	ft_putstr("std:");
	printf("(%i)\n", printf(""));
	ft_putstr("ft_:");
	printf("(%i)\n", ft_printf(""));
	ft_putstr("\n");
	ft_putendl("printf(\"%%\")");
	ft_putstr("std:");
	printf("(%i)\n", printf("%%"));
	ft_putstr("ft_:");
	printf("(%i)\n", ft_printf("%%"));
	ft_putstr("\n");
	ft_putendl("printf(\"%5%\")");
	ft_putstr("std:");
	printf("(%i)\n", printf("%5%"));
	ft_putstr("ft_:");
	printf("(%i)\n", ft_printf("%5%"));
	ft_putstr("\n");
	ft_putendl("printf(\"%-5%\")");
	ft_putstr("std:");
	printf("(%i)\n", printf("%-5%"));
	ft_putstr("ft_:");
	printf("(%i)\n", ft_printf("%-5%"));
	ft_putstr("\n");
	ft_putendl("printf(\"%   %\")");
	ft_putstr("std:");
	printf("(%i)\n", printf("%   %"));
	ft_putstr("ft_:");
	printf("(%i)\n", ft_printf("%   %"));
	ft_putstr("\n");
	ft_putendl("printf(\"%+%\")");
	ft_putstr("std:");
	printf("(%i)\n", printf("%+%"));
	ft_putstr("ft_:");
	printf("(%i)\n", ft_printf("%+%"));
	ft_putstr("\n");
	ft_putendl("printf(\"% .3%\")");
	ft_putstr("std:");
	printf("(%i)\n", printf("% .3%"));
	ft_putstr("ft_:");
	printf("(%i)\n", ft_printf("% .3%"));
	ft_putstr("\n");
# endif
# ifdef HEX
	ft_putendl("printf(\"%x\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%x", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%x", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%X\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%X", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%X", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%10x\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%10x", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%10x", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%-10x\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-10x", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%-10x", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#08x\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#08x", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#08x", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#-08x\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#-08x", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#-08x", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#8x\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#8x", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#8x", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#-8x\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#-8x", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#-8x", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#x\", 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#x", 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#x", 0));
	ft_putstr("\n");
	ft_putendl("printf(\"%#X\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#X", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#X", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#.x, %#.0x\", 0, 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#.x, %#.0x", 0, 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#.x, %#.0x", 0, 0));
	ft_putstr("\n");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#5.x, %#5.0x", 0, 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#5.x, %#5.0x", 0, 0));
	ft_putstr("\n");
# endif
# ifdef OCTAL
	ft_putendl("printf(\"%o\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%o", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%o", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%o\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%o", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%o", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%10o\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%10o", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%10o", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%-10o\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-10o", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%-10o", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#08o\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#08o", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#08o", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#-08o\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#-08o", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#-08o", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#8o\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#8o", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#8o", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#-8o\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#-8o", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#-8o", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#o\", 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#o", 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#o", 0));
	ft_putstr("\n");
	ft_putendl("printf(\"%#o\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#o", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#o", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#.o, %#.0o\", 0, 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#.o, %#.0o", 0, 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#.o, %#.0o", 0, 0));
	ft_putstr("\n");
	ft_putendl("printf(\"%#5.o, %#5.0o\", 0, 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#5.o, %#5.0o", 0, 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#5.o, %#5.0o", 0, 0));
	ft_putstr("\n");
	ft_putendl("printf(\"%.o, %.0o\", 0, 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%.o, %.0o", 0, 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%.o, %.0o", 0, 0));
	ft_putstr("\n");
	ft_putendl("printf(\"%5.o, %5.0o\", 0, 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%5.o, %5.0o", 0, 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%5.o, %5.0o", 0, 0));
	ft_putstr("\n");
	ft_putendl("printf(\"%o\", 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%o", 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%o", 0));
	ft_putstr("\n");
# endif
# ifdef UNSIGNED
	ft_putendl("printf(\"%u\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%u", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%u", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%u\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%u", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%u", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%10u\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%10u", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%10u", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%-10u\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-10u", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%-10u", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#08u\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#08u", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#08u", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#-08u\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#-08u", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#-08u", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#8u\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#8u", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#8u", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#-8u\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#-8u", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#-8u", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#u\", 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#u", 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#u", 0));
	ft_putstr("\n");
	ft_putendl("printf(\"%#u\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#u", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#u", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#.u, %#.0u\", 0, 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#.u, %#.0u", 0, 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#.u, %#.0u", 0, 0));
	ft_putstr("\n");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#5.u, %#5.0u", 0, 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#5.u, %#5.0u", 0, 0));
	ft_putstr("\n");
# endif
# ifdef CHAR
	ft_putendl("printf(\"%c\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%c", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%c", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%c\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%c", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%c", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%10c\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%10c", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%10c", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%-10c\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-10c", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%-10c", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#08c\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#08c", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#08c", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#-08c\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#-08c", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#-08c", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#8c\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#8c", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#8c", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#-8c\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#-8c", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#-8c", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#c\", 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#c", 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#c", 0));
	ft_putstr("\n");
	ft_putendl("printf(\"%#c\", 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#c", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#c", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%#.c, %#.0c\", 0, 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#.c, %#.0c", 0, 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#.c, %#.0c", 0, 0));
	ft_putstr("\n");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#5.c, %#5.0c", 0, 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#5.c, %#5.0c", 0, 0));
	ft_putstr("\n");
	ft_putendl("printf(\"%#.2c, NULL)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%#.2c", NULL));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%#.2c", NULL));
	ft_putstr("\n");
	ft_putendl("printf(\"%# c, 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%# c", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%# c", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%# .3c, 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%# .3c", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%# .3c", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%.2c, NULL)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%.2c", NULL));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%.2c", NULL));
	ft_putstr("\n");
# endif
# ifdef DIGIT
	ft_putendl("printf(\"%5d, -42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%5d", -42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%5d", -42));
	ft_putstr("\n");
	ft_putendl("printf(\"%+5d, 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%+5d", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%+5d", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%0+5d, 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%0+5d", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%0+5d", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%0+5d, -42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%0+5d", -42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%0+5d", -42));
	ft_putstr("\n");
	ft_putendl("printf(\"%05d, -42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%05d", -42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%05d", -42));
	ft_putstr("\n");
	ft_putendl("printf(\"%-05d, 42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-05d", 42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%-05d", 42));
	ft_putstr("\n");
	ft_putendl("printf(\"%-05d, -42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-05d", -42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%-05d", -42));
	ft_putstr("\n");
	ft_putendl("printf(\"%-5d, -42)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-5d", -42));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%-5d", -42));
	ft_putstr("\n");
	ft_putendl("printf(\"%-9.6d, 4242)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%-9.6d", 4242));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%-9.6d", 4242));
	ft_putstr("\n");
	ft_putendl("printf(\"%9.6d, 4242)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%9.6d", 4242));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%9.6d", 4242));
	ft_putstr("\n");
	ft_putendl("printf(\"%.6d, -4242)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%.6d", -4242));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%.6d", -4242));
	ft_putstr("\n");
	ft_putendl("printf(\"% 10.5d, 4242)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("% 10.5d", 4242));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("% 10.5d", 4242));
	ft_putstr("\n");
	ft_putendl("printf(\"%07.2d, 0)");
	ft_putstr("std:");
	printf(" (%i)\n", printf("%07.2d", 0));
	ft_putstr("ft_:");
	printf(" (%i)\n", ft_printf("%07.2d", 0));
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
