#include <libft.h>

void	*ft_memchr(void const *s, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (((char const *)s)[i] == c)
			return ((void *)&(((char const *)s)[i]));
		i++;
	}
	return (NULL);
}
