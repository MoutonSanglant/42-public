/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:38:20 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/05 23:43:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_bzero(void *s, size_t n)
{
	if (!s)
	{
		ERROR_PARAM("ft_bzero");
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
