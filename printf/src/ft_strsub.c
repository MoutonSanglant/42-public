/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:17 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 19:22:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str_new;
	size_t	i;

	if (!s)
	{
		ft_putendl("ft_strsub error:\nsent parameter is NULL.");
		return (NULL);
	}
	str_new = ft_strnew(len);
	if (str_new)
	{
		i = 0;
		while (i < len)
		{
			str_new[i] = s[start + i];
			i++;
		}
		str_new[i] = '\0';
	}
	return (str_new);
}

#else

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str_new;
	size_t	i;

	str_new = ft_strnew(len);
	if (str_new)
	{
		i = 0;
		while (i < len)
		{
			str_new[i] = s[start + i];
			i++;
		}
		str_new[i] = '\0';
	}
	return (str_new);
}
#endif
