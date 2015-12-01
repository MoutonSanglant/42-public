#include <libft.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new_str;
	int	i;

	new_str = ft_strnew (sizeof(char) * (ft_strlen(s) + 1));	
	if (new_str)
	{
		i = 0;
		while(s[i] != '\0')
		{
			new_str[i] = f(s[i]);
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}
