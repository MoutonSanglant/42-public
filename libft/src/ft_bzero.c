#include <libft.h>

void	ft_bzero (void *b, size_t len)
{
	ft_memset(b, '\0', len);
}
