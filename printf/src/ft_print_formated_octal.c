/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_octal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:47:23 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/24 09:58:16 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_print_formated_octal(va_list ap, t_fdata *fdatas)
{
	char	*str;
	int		nb;

	str = NULL;
	if (fdatas->length == LENGTH_NONE)
		str = ft_uitoa_base(va_arg(ap, unsigned int), 10);
	else if (fdatas->length == LENGTH_HH)
		str = ft_uitoa_base((unsigned char)va_arg(ap, unsigned int), 10);
	else if (fdatas->length == LENGTH_H)
		str = ft_uitoa_base((unsigned short int)va_arg(ap, unsigned int), 10);
	else if (fdatas->length == LENGTH_L)
		str = ft_uitoa_base((unsigned long int)va_arg(ap, unsigned long int), 10);
	else if (fdatas->length == LENGTH_LL)
		str = ft_uitoa_base((unsigned long long int)va_arg(ap, unsigned long long int), 10);
	else if (fdatas->length == LENGTH_J)
		str = ft_uitoa_base((uintmax_t)va_arg(ap, uintmax_t), 10);
	else if (fdatas->length == LENGTH_Z)
		str = ft_uitoa_base((size_t)va_arg(ap, size_t), 10);

	if (fdatas->flag & FLAG_NUMBERSIGN)
		ft_strprepend(&str, "0");
	nb = va_arg(ap, int);
	str = ft_itoa_base(nb, 8);
	fdatas->bcount += ft_putstr(str);
	ft_strdel(&str);
}
