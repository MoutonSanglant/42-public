#include <libft.h>

void	*ft_memccpy(void *dest, void const *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((char*)src)[i] == c)
			return (&((char*)dest)[i + 1]);

		((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
	return (NULL);
}
