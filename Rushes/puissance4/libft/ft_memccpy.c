/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:09:03 by gdruel            #+#    #+#             */
/*   Updated: 2015/01/27 17:25:57 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t		i;
	char		*a;
	const char	*b;

	a = (char *)dst;
	b = (char *)src;
	i = 0;
	while (i < n)
	{
		a[i] = b[i];
		if (a[i] == c)
			return (&a[i + 1]);
		i++;
	}
	return (NULL);
}
