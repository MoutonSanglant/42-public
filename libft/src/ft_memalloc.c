#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void		*addr;
	unsigned int	i;

	addr = malloc(size);
	if (addr)
	{
		i = 0;
		while(i < size)
			((char *)addr)[i++] = 0;
	}
	return addr;
}
