#include <libft.h>

char	*ft_strncat(char *dest, char const *src, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = dest;
	while (*ptr++);
	ptr--;
	i = 0;
	while (i < n)
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (dest);
}
