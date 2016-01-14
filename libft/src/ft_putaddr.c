/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 00:40:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/14 04:49:21 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putaddr(const void *addr)
{
	char	*str;

	str = ft_itoa_base((int)addr, 16);
	ft_putstr("0x");
	ft_putstr(str);
}
