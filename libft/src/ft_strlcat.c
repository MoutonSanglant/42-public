/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:34:31 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/14 11:51:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	char	*ptr;
	size_t	total_size;
	size_t	src_len;
	size_t	max;
	size_t	i;

	src_len = ft_strlen(src);
	ptr = dst;
	i = 0;
	while (*ptr)
	{
		if (i++ >= size)
			return (size + src_len);
		ptr++;
	}
	i = 0;
	total_size = ft_strlen(dst) + src_len;
	max = size - (total_size - src_len) - (1 * sizeof(char));
	while (i < max && src[i])
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (total_size);
}
