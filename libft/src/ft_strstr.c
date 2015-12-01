#include <libft.h>

char	*ft_strstr(char const *haystack, char const *needle)
{
	char const	*ptr;
	char const	*ptr_haystack;

	while (*haystack)
	{
		ptr = needle;
		ptr_haystack = haystack;
		while (*ptr == *ptr_haystack)
		{
			ptr++;
			ptr_haystack++;
		}
		if (!*ptr)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
