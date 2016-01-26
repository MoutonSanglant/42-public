/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:38:20 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 19:25:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_bzero(void *s, size_t n)
{
	if (!s)
	{
		ft_putendl("ft_bzero error:\nsent parameter is NULL.");
		return ;
	}
	ft_memset(s, '\0', n);
}

#else

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
#endif
