/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:34:06 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 20:05:40 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

int		ft_memcmp(void const *s1, void const *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	if (!s1 || !s2)
	{
		ft_putendl("ft_memcmp returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (-1);
	}
	i = 0;
	while (i < n)
	{
		c1 = ((unsigned char*)s1)[i];
		c2 = ((unsigned char*)s2)[i];
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	return (0);
}

#else

int		ft_memcmp(void const *s1, void const *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (i < n)
	{
		c1 = ((unsigned char*)s1)[i];
		c2 = ((unsigned char*)s2)[i];
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	return (0);
}
#endif
