/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:29 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/03 10:03:19 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memccpy(void *dst, void const *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char const *)src)[i] == c)
			return (&((unsigned char *)dst)[i + 1]);
		((unsigned char *)dst)[i] = ((unsigned char const *)src)[i];
		i++;
	}
	return (NULL);
}
