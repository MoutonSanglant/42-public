/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 00:40:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/14 15:24:59 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putaddr(const void *addr)
{
	char	*str;

	str = ft_itoa_base((uint64_t)addr, 16);
	ft_putstr("0x");
	ft_putstr(str);
}
