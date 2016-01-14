/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:16 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/14 14:31:33 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dst, void const *src, size_t len)
{
	char		*ptr_dst;
	const char	*ptr_src;
	size_t		i;

	if (len == 0 || dst == src)
		return (dst);
	ptr_dst = (char *)dst;
	ptr_src = (const char *)src;
	if ((unsigned long)ptr_dst < (unsigned long)ptr_src)
	{
		i = 0;
		while (i < len)
		{
			ptr_dst[i] = ptr_src[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i-- > 0)
			ptr_dst[i] = ptr_src[i];
		ptr_dst[0] = ptr_src[0];
	}
	return (dst);
}
