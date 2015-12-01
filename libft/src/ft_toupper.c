#include <libft.h>

int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c - 40);
	return (c);
}
