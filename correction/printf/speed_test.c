#include <stdio.h>
#include <limits.h>

#ifdef FT
# include <libftprintf.h>
# define print ft_printf
#else
# define print printf
#endif
#define MAX_ITER 100000

int		main(void)
{
	int i = 0;

	while (i < MAX_ITER)
	{
		print("%jx", -4294967296);
		fflush(stdout);

		print("%jx", -4294967297);
		fflush(stdout);

		print("%010x", 542);
		fflush(stdout);

		print("%08x", 42);
		fflush(stdout);

		print("%hhd", 128);
		fflush(stdout);

		print("%hhd", -129);
		fflush(stdout);

		print("%zhd", 4294967296);
		fflush(stdout);

		print("%jhd", 9223372036854775807);
		fflush(stdout);

		print("\n");
		fflush(stdout);

		print("%%");
		fflush(stdout);

		print("%d", 42);
		fflush(stdout);

		print("%ld", 2147483647);
		fflush(stdout);

		print("%lld", 9223372036854775807);
		fflush(stdout);

		print("%c", 75);
		fflush(stdout);

		print("%C", 8000);
		fflush(stdout);

		print("%C", 80000);
		fflush(stdout);

		print("%C", L'α');
		fflush(stdout);

		print("{%5p}",  0);
		fflush(stdout);

		print("{%-15p}", 0);
		fflush(stdout);

		print("{%10RN}");
		fflush(stdout);

		print("%s%d%p%%%S%D%i%o%O%u%U%x%X%c%C", "bonjour", 42, &i, L"暖炉", LONG_MAX, 42, 42, 42, 100000, ULONG_MAX, 42, 42, 'c', L'플');
		fflush(stdout);

		i++;
	}

	return (0);
}
