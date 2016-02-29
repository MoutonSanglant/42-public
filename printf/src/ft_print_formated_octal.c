/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_octal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:47:23 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/29 10:49:50 by tdefresn         ###   ########.fr       */
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

static char		*str_from_arg(va_list ap, t_fdata *fdatas)
{
	if (fdatas->length == LENGTH_NONE)
		return (ft_itoa_base(va_arg(ap, unsigned int), 8));
	else if (fdatas->length & LENGTH_Z)
		return (ft_itoa_base((size_t)va_arg(ap, size_t), 8));
	else if (fdatas->length & LENGTH_J)
		return (ft_itoa_base((uintmax_t)va_arg(ap, uintmax_t), 8));
	else if (fdatas->length & LENGTH_LL)
		return (ft_itoa_base((unsigned long long int)va_arg(ap, unsigned long long int), 8));
	else if (fdatas->length & LENGTH_L)
		return (ft_itoa_base((unsigned long int)va_arg(ap, unsigned long int), 8));
	else if (fdatas->length & LENGTH_H)
		return (ft_itoa_base((unsigned short int)va_arg(ap, unsigned int), 8));
	else if (fdatas->length & LENGTH_HH)
		return (ft_itoa_base((unsigned char)va_arg(ap, unsigned int), 8));
	return (NULL);
}

void			ft_print_formated_octal(va_list ap, t_fdata *fdatas)
{
	char	*str;

	str = str_from_arg(ap, fdatas);
	if (str[0] == '0'
			&& (fdatas->precision == 0 || fdatas->flag & FLAG_NUMBERSIGN))
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
		if (!(fdatas->flag & FLAG_MORE
					|| fdatas->flag & FLAG_SPACE) || fdatas->width > 1)
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
