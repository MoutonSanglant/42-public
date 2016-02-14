/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:35:58 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:23:39 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

char	*ft_strnstr(char const *s1, char const *s2, size_t n)
{
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
	{
		ft_putendl("ft_strnstr returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		j = 0;
		while (s2[j] && s1[i + j] == s2[j] && (i + j) < n)
			j++;
		if (!s2[j])
			return (&((char *)s1)[i]);
		if (!s1[i])
			break ;
		i++;
	}
	return (NULL);
}

#else

char	*ft_strnstr(char const *s1, char const *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (s2[j] && s1[i + j] == s2[j] && (i + j) < n)
			j++;
		if (!s2[j])
			return (&((char *)s1)[i]);
		if (!s1[i])
			break ;
		i++;
	}
	return (NULL);
}
#endif
