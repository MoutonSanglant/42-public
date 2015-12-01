/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:37 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/01 12:43:25 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memalloc(size_t size)
{
	void	*addr;
	size_t	i;

	addr = malloc(size);
	if (addr)
	{
		i = 0;
		while (i < size)
			((char *)addr)[i++] = 0;
	}
	return (addr);
}
