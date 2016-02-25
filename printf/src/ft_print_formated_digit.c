/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_digit.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:32:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/25 14:42:05 by tdefresn         ###   ########.fr       */
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

void	ft_print_formated_digit(va_list ap, t_fdata *fdatas)
{
	char	*str;

	str = NULL;
	if (fdatas->length == LENGTH_NONE)
		str = ft_itoa(va_arg(ap, int));
	else if (fdatas->length == LENGTH_HH)
		str = ft_itoa((signed char)va_arg(ap, int));
	else if (fdatas->length == LENGTH_H)
		str = ft_itoa((short int)va_arg(ap, int));
	else if (fdatas->length == LENGTH_L)
		str = ft_imaxtoa((long int)va_arg(ap, long int));
	else if (fdatas->length == LENGTH_LL)
		str = ft_imaxtoa((long long int)va_arg(ap, long long int));
	else if (fdatas->length == LENGTH_J)
		str = ft_imaxtoa((intmax_t)va_arg(ap, intmax_t));
	else if (fdatas->length == LENGTH_Z)
		str = ft_imaxtoa((size_t)va_arg(ap, size_t));
	if (str[0] == '0')
	{
		if (fdatas->precision == 0)
			str[0] = '\0';
		fdatas->flag ^= (fdatas->flag & FLAG_NUMBERSIGN) ? FLAG_NUMBERSIGN : FLAG_ZERO;
	}
	fdatas->precision = fdatas->precision - ft_strlen(str);
	fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
	fdatas->width = fdatas->width - fdatas->precision - ft_strlen(str);
	if (fdatas->flag & FLAG_LESS)
		justify(str, fdatas);
	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE || fdatas->flag & FLAG_SPACE) || fdatas->width > 1)
			fdatas->bcount += write(1, &fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		justify(str, fdatas);
	ft_strdel(&str);
}
