/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_hex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:37:24 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/24 09:38:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		justify(char *str, t_fdata *fdatas)
{
	if (fdatas->flag & FLAG_MORE && str[0] != '-')
		fdatas->bcount += write(1, "+", 1);
	else if (str[0] == '-')
	{
		if (fdatas->precision > 0)
		{
			fdatas->bcount += write(1, "-", 1);
			str[0] = '0';
		}
	}
	else if (fdatas->flag & FLAG_SPACE)
		fdatas->bcount += write(1, " ", 1);
	while (fdatas->precision-- > 0)
		fdatas->bcount += write(1, "0", 1);
	fdatas->bcount += ft_putstr(str);
}

void	ft_print_formated_hex(va_list ap, t_fdata *fdatas)
{
	char	*str;

	str = NULL;
	if (fdatas->length == LENGTH_NONE)
		str = ft_uitoa_base((uintmax_t)va_arg(ap, unsigned int), 16);
	else if (fdatas->length == LENGTH_HH)
		str = ft_uitoa_base((uintmax_t)va_arg(ap, unsigned int), 16);
	else if (fdatas->length == LENGTH_H)
		str = ft_uitoa_base((uintmax_t)va_arg(ap, unsigned int), 16);
	else if (fdatas->length == LENGTH_L)
		str = ft_uitoa_base((uintmax_t)va_arg(ap, unsigned long int), 16);
	else if (fdatas->length == LENGTH_LL)
		str = ft_uitoa_base((uintmax_t)va_arg(ap, unsigned long long int), 16);
	else if (fdatas->length == LENGTH_J)
		str = ft_uitoa_base((uintmax_t)va_arg(ap, uintmax_t), 16);
	else if (fdatas->length == LENGTH_Z)
		str = ft_uitoa_base((uintmax_t)va_arg(ap, size_t), 16);

	if (str[0] == '0')
	{
		if (fdatas->precision == 0)
			str[0] = '\0';
		fdatas->flag ^= (fdatas->flag & FLAG_NUMBERSIGN) ? FLAG_NUMBERSIGN : FLAG_ZERO;
	}
	if (fdatas->specifier == 'X')
	{
		int i = 0;

		while (str[i])
		{
			str[i] = (char)ft_toupper(str[i]);
			i++;
		}
	}

	fdatas->precision = fdatas->precision - ft_strlen(str);
	fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
	fdatas->width = fdatas->width - fdatas->precision - ft_strlen(str);
	if (fdatas->flag & FLAG_NUMBERSIGN)
	{
		fdatas->width -= 2;
		if (fdatas->flag & FLAG_ZERO)
			fdatas->bcount += write(1, (fdatas->specifier == 'x') ? "0x" : "0X", 2);
	}
	if (fdatas->flag & FLAG_LESS)
	{
		if (fdatas->flag & FLAG_NUMBERSIGN && !(fdatas->flag & FLAG_ZERO))
			fdatas->bcount += write(1, (fdatas->specifier == 'x') ? "0x" : "0X", 2);
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
			fdatas->bcount += write(1, (fdatas->specifier == 'x') ? "0x" : "0X", 2);
		justify(str, fdatas);
	}

	//fdatas->bcount += ft_putstr(str);
	ft_strdel(&str);
}
