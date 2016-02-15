#include <stdio.h>
#include <libft.h>

int main(void)
{
	wchar_t	*wstr = L"a sample wide string";
	char	*str = "a sample string";
	//wint_t	wnb = 42;
	int		nb = 42;
	// sS  string of characters
	// p   pointer adresse
	// dD  signed decimal integer
	// i   signed decimal integer
	// oO  unsigned octal
	// uU  unsigned decimal integer
	// xX  unsigned hexadecimal integer lowercase / uppercase
	// cC  character
	ft_putendl("Test: %%");
	printf("std: %%\n");
	ft_printf("ft_: %%\n");
	ft_putstr("\n");

	ft_putendl("Test: %s %S");
	printf("std: %s\n", str);
	printf("std: %s\n", "a random string");
	printf("std: %S\n", wstr);
	printf("std: %S\n", L"another random string");
	//ft_printf("ft_: %%\n");
	ft_putstr("\n");

	ft_putendl("Test: %p");
	printf("std: %p\n", str);
	ft_putstr("\n");

	ft_putendl("Test: %d %D");
	printf("std: %d\n", nb);
	printf("std: %D\n", nb);
	ft_putstr("\n");

	ft_putendl("Test: %i");
	printf("std: %i\n", nb);
	ft_putstr("\n");

	ft_putendl("Test: %o %O");
	printf("std: %o\n", nb);
	printf("std: %O\n", nb);
	ft_putstr("\n");

	ft_putendl("Test: %u %U");
	printf("std: %u\n", nb);
	printf("std: %U\n", nb);
	ft_putstr("\n");

	ft_putendl("Test: %x %X");
	printf("std: %x\n", nb);
	printf("std: %X\n", nb);
	ft_putstr("\n");

	ft_putendl("Test: %c");
	printf("std: %c\n", nb);
	ft_putstr("\n");

	return (0);
}
