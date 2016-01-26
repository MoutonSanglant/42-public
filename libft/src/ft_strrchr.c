/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:33:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:25:05 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

char	*ft_strrchr(const char *s, int c)
{
	int64_t	i;

	if (!s)
	{
		ft_putendl("ft_strrchr returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (NULL);
	}
	i = ft_strlen(s);
	if ((char)c == '\0')
		return (&((char *)s)[i]);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

#else

char	*ft_strrchr(const char *s, int c)
{
	int64_t	i;

	i = ft_strlen(s);
	if ((char)c == '\0')
		return (&((char *)s)[i]);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
#endif
