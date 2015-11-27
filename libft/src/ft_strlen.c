#include <string.h>

size_t	ft_strlen(char const *s)
{
	size_t i;
	
	i = 0;
	while(*s++ != '\0')
		i++;

	return i;
}
