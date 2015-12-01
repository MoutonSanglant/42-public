/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:26 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/01 12:37:28 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memchr(void const *s, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (((char const *)s)[i] == c)
			return ((void *)&(((char const *)s)[i]));
		i++;
	}
	return (NULL);
}
