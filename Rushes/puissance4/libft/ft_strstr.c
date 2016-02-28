/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 12:08:46 by gdruel            #+#    #+#             */
/*   Updated: 2014/11/14 13:48:02 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strstr(const char *s1, const char *s2)
{
	int i;
	int j;
	int size;

	size = ft_strlen(s2);
	i = 0;
	j = 0;
	if (size == 0)
		return ((char *)s1);
	while (s1[i] != '\0')
	{
		if (s1[i] == s2[j])
		{
			while (s1[i + j] == s2[j])
			{
				j++;
				if (j == size)
					return ((char *)&s1[i]);
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
