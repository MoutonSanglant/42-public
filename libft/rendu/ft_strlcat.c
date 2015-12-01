/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:34:31 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/01 12:34:32 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	char	*ptr;
	size_t	i;
	size_t	total_size;
	size_t	max;

	total_size = ft_strlen(dst) + ft_strlen(src);
	max = size - ft_strlen(dst) - 1 * sizeof(char);
	ptr = dst;
	i = 0;
	while (*ptr)
	{
		if (i > size)
			return (size + ft_strlen(src));
		i++;
		ptr++;
	}
	i = 0;
	while (i < max && src[i])
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i + 1] = '\0';
	return (total_size);
}
