/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 18:22:26 by gdruel            #+#    #+#             */
/*   Updated: 2014/11/14 13:57:22 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char	*s;
	void	*t;
	size_t	i;

	i = 0;
	t = NULL;
	if (size == 0)
		return (NULL);
	s = (char *)malloc(sizeof(*s) * (size));
	if (s)
	{
		while (i < size)
		{
			s[i] = 0;
			i++;
		}
		t = (void *)s;
	}
	return (t);
}
