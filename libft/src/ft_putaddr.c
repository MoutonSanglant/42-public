/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 00:40:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 20:11:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putaddr(const void *addr)
{
	char	*str;

	ft_putstr("0x");
	str = ft_itoa_base((uintptr_t)addr, 16);
	ft_putstr(str);
	ft_strdel(&str);
}
