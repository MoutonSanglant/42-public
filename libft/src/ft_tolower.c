#include <libft.h>

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c + 40);
	return (c);
}
