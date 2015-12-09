/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:16 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/03 10:04:10 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dst, void const *src, size_t len)
{
	size_t	i;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * len);
	i = 0;
	while (i < len)
	{
		buffer[i] = ((char*)src)[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		((char*)dst)[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (dst);
}
