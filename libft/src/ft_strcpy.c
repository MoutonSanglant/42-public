char	*ft_strcpy(char *dest, char const *src)
{
	char *ptr;

	ptr = dest;
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
