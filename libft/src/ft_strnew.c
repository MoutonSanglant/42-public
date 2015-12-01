#include <libft.h>

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(size);
	if (str)
	{
		i = 0;
		while (i < size)
			str[i++] = '\0';
		str[i] = '\0';
	}
	return str;
}
