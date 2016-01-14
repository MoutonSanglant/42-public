#include "includes/libft.h"
#include <stdio.h>

int main(void)
{
	char *a;
	void *b;

	a = (char *) malloc(sizeof(char) * 17);
	b = (void *) malloc(83);
	ft_putaddr(NULL);
	ft_putchar('\n');
	ft_putaddr((void *)0x1f56e4);
	ft_putchar('\n');
	ft_putaddr((void *)0x7ff6d2c031d0);
	ft_putchar('\n');
	ft_putaddr(a);
	ft_putchar('\n');
	ft_putaddr(b);
	ft_putchar('\n');
	printf("a: %p\nb: %p\n", a, b);
	ft_putendl(ft_itoa_base(0, 10));
	ft_putendl(ft_itoa_base(-1, 10));
	ft_putendl(ft_itoa_base(1, 10));
	ft_putendl(ft_itoa_base(42, 10));
	ft_putendl(ft_itoa_base(-42, 10));
	ft_putendl(ft_itoa_base(9999, 10));
	ft_putendl(ft_itoa_base(-9999, 10));
	ft_putendl(ft_itoa_base(2147483647, 10));
	ft_putendl(ft_itoa_base(2147483648, 10));
	ft_putendl(ft_itoa_base(2147483649, 10));
	ft_putendl(ft_itoa_base(-2147483647, 10));
	ft_putendl(ft_itoa_base(-2147483648, 10));

	return (0);
}
