/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:34:28 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:13:45 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_new;
	char	*ptr;

	if (!s1 || !s2)
	{
		ft_putendl("ft_strjoin returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (NULL);
	}
	str_new = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (str_new)
	{
		ptr = str_new;
		while (*s1)
			*ptr++ = *s1++;
		while (*s2)
			*ptr++ = *s2++;
		*++ptr = '\0';
	}
	return (str_new);
}

#else

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_new;
	char	*ptr;

	str_new = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (str_new)
	{
		ptr = str_new;
		while (*s1)
			*ptr++ = *s1++;
		while (*s2)
			*ptr++ = *s2++;
		*++ptr = '\0';
	}
	return (str_new);
}
#endif
