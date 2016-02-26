/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_pointer.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:49:08 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/26 18:44:47 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_print_formated_pointer(va_list ap, t_fdata *fdatas)
{
	char	*str;

	str = va_arg(ap, char *);
	fdatas->bcount += (str) ? ft_putaddr(str) : ft_putstr("0x0");
}
