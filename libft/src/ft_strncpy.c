#include <libft.h>

char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	size_t i;
	size_t	max;

	max = ft_strlen(src);
	i = 0;
	while (i < n)
	{
		if (i < max)
			dest[i] = src[i];
		else
			dest[i] = '\0';
		i++;
	}
	return (dest);
}
