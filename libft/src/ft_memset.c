/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:04:18 by tdefresn          #+#    #+#             */
/*   Updated: 2015/11/24 18:41:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memset (void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	while(i < len)
		((char *)b)[i++] = c;
	return b;
}
