#include <libft.h>

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	// ghi
	// gha
	// 012
	
	n -= 1;
	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);

}
