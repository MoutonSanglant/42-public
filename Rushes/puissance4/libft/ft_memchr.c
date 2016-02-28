/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 12:38:21 by gdruel            #+#    #+#             */
/*   Updated: 2014/11/14 13:38:41 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	void			*s2;

	i = 0;
	str = (unsigned char *)s;
	if (!s || !n)
		return (NULL);
	while (i != n)
	{
		if (str[i] == (unsigned char)c)
		{
			s2 = (char *)&str[i];
			return (s2);
		}
		i++;
	}
	return (NULL);
}
