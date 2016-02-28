/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 13:00:03 by gdruel            #+#    #+#             */
/*   Updated: 2014/11/14 13:48:51 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			j;
	size_t			size;

	i = 0;
	j = 0;
	if (!s2 || !s2[i])
		return ((char *)s1);
	size = ft_strlen(s2);
	while (s1[i] && i < n)
	{
		while (s1[i + j] == s2[j] && (i + j) < n)
		{
			if (j == size - 1)
				return ((char *)&s1[i]);
			j++;
		}
		i++;
		j = 0;
	}
	return (NULL);
}
