#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	int	i;

	new_str = ft_strnew (sizeof(char) * (ft_strlen(s) + 1));
	if (new_str)
	{
		i = 0;
		while(s[i] != '\0')
		{
			new_str[i] = f(i, s[i]);
			i++;
		}
		new_str[i] = '\0';
	}
	
	return (new_str);
}
