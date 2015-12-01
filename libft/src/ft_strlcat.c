#include <libft.h>

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t	i;
	char	*ptr;
	size_t	total_size;
	size_t	max;

	total_size = ft_strlen(dst) + ft_strlen(src);
	max = size - ft_strlen(dst) - 1 * sizeof(char);
	ptr = dst;
	while (*ptr++);
	ptr--;
	i = 0;
	while (src[i])
	{
		if (i >= max)
			return (size);
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (total_size);
}
