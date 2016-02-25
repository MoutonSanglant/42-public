/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_octal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:47:23 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/25 16:16:29 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		justify(char *str, t_fdata *fdatas)
{
	if (str[0] == '-')
	{
		if (fdatas->precision > 0)
		{
			fdatas->bcount += write(1, "-", 1);
			str[0] = '0';
		}
	}
	else if (fdatas->flag & FLAG_MORE)
		fdatas->bcount += write(1, "+", 1);
	else if (fdatas->flag & FLAG_SPACE)
		fdatas->bcount += write(1, " ", 1);
	while (fdatas->precision-- > 0)
		fdatas->bcount += write(1, "0", 1);
	fdatas->bcount += ft_putstr(str);
}

void	ft_print_formated_octal(va_list ap, t_fdata *fdatas)
{
	char	*str;

	str = NULL;
	if (fdatas->length == LENGTH_NONE)
		str = ft_uitoa_base(va_arg(ap, unsigned int), 8);
	else if (fdatas->length == LENGTH_HH)
		str = ft_uitoa_base((unsigned char)va_arg(ap, unsigned int), 8);
	else if (fdatas->length == LENGTH_H)
		str = ft_uitoa_base((unsigned short int)va_arg(ap, unsigned int), 8);
	else if (fdatas->length == LENGTH_L)
		str = ft_uitoa_base((unsigned long int)va_arg(ap, unsigned long int), 8);
	else if (fdatas->length == LENGTH_LL)
		str = ft_uitoa_base((unsigned long long int)va_arg(ap, unsigned long long int), 8);
	else if (fdatas->length == LENGTH_J)
		str = ft_uitoa_base((uintmax_t)va_arg(ap, uintmax_t), 8);
	else if (fdatas->length == LENGTH_Z)
		str = ft_uitoa_base((size_t)va_arg(ap, size_t), 8);
	if (str[0] == '0' && (fdatas->precision == 0 || fdatas->flag & FLAG_NUMBERSIGN))
		str[0] = '\0';
	fdatas->precision = fdatas->precision - ft_strlen(str);
	fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
	fdatas->width = fdatas->width - fdatas->precision - ft_strlen(str);
	if (fdatas->flag & FLAG_NUMBERSIGN)
	{
		fdatas->width--;
		if (fdatas->flag & FLAG_ZERO)
			fdatas->bcount += write(1, "0", 1);
	}
	if (fdatas->flag & FLAG_LESS)
	{
		if (fdatas->flag & FLAG_NUMBERSIGN && !(fdatas->flag & FLAG_ZERO))
			fdatas->bcount += write(1, "0", 1);
		justify(str, fdatas);
	}
	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE || fdatas->flag & FLAG_SPACE) || fdatas->width > 1)
			fdatas->bcount += write(1, &fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
	{
		if (fdatas->flag & FLAG_NUMBERSIGN && !(fdatas->flag & FLAG_ZERO))
			fdatas->bcount += write(1, "0", 1);
		justify(str, fdatas);
	}
	ft_strdel(&str);
}
