#include <libft.h>

char	*ft_strtrim(char const *s)
{
	char		*str_new;
	int		first_char;
	int		last_char;
	unsigned int	len;
	unsigned int	i;

	first_char = 0;
	last_char = 0;

	len = 0;
	while (*s != '\0')
	{
		if (*s != ' ' && *s != '\n' && *s != '\t')
		{
			if (first_char == 0)
				first_char = (int) s;
			last_char = (int) s;
			len = 1;
		}
		s++;
	}
	len += last_char - first_char;
	str_new = ft_strnew(sizeof(char) * len);
	if (str_new)
	{
		s =(char *)first_char;
		i = 0;
		while (i < len)
		{
			str_new[i] = *s++;
			i++;
		}
		str_new[i] = '\0';
	}
	return(str_new);
}
