#include <libft.h>
#include <string.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*str_new;
	unsigned int	i;

	str_new = ft_strnew(len);
	if (str_new)
	{
		i = 0;
		while (i < len)
		{
			str_new[i] = s[start + i];
			i++;
		}
	}
	return (str_new);
}
