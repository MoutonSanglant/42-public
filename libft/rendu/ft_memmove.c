/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:16 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/01 12:37:17 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dest, void const *src, size_t n)
{
	size_t	i;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * n);
	i = 0;
	while (i < n)
	{
		buffer[i] = ((char*)src)[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		((char*)dest)[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (dest);
}
