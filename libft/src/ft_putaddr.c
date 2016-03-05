/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 00:40:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/06 00:08:57 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	NOTE
**	This is not the standard "ft_putaddr" since
**	it returns a value when it shouldn't.
**	===================================
**	void	ft_putaddr(const void *addr)
*/

int		ft_putaddr(const void *addr)
{
	char	*str;
	int		bcount;

	bcount = 0;
	bcount += ft_putstr("0x");
	str = ft_itoa_base((uintptr_t)addr, 16);
	bcount += ft_putstr(str);
	ft_strdel(&str);
	return (bcount);
}
