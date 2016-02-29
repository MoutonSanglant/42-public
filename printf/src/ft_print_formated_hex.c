/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_hex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:37:24 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/29 10:59:26 by tdefresn         ###   ########.fr       */
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

static char		*str_from_arg(va_list ap, t_fdata *fdatas)
{
	if (fdatas->length == LENGTH_NONE)
		return (ft_itoa_base((unsigned int)va_arg(ap, unsigned int), 16));
	else if (fdatas->length & LENGTH_Z)
		return (ft_itoa_base((size_t)va_arg(ap, size_t), 16));
	else if (fdatas->length & LENGTH_J)
		return (ft_itoa_base((uintmax_t)va_arg(ap, uintmax_t), 16));
	else if (fdatas->length & LENGTH_LL)
		return (ft_itoa_base((uint64_t)va_arg(ap, uint64_t), 16));
	else if (fdatas->length & LENGTH_L)
		return (ft_itoa_base((unsigned long)va_arg(ap, unsigned long), 16));
	else if (fdatas->length & LENGTH_H)
		return (ft_itoa_base((unsigned int)va_arg(ap, unsigned int), 16));
	else if (fdatas->length & LENGTH_HH)
		return (ft_itoa_base((unsigned int)va_arg(ap, unsigned int), 16));
	return (NULL);
}

void	ft_print_formated_hex(va_list ap, t_fdata *fdatas, char specifier)
{
	char	*str;
	int		len;
	int		i;

	str = str_from_arg(ap, fdatas);
	if (str[0] == '0')
	{
		if (fdatas->precision == 0)
			str[0] = '\0';
		fdatas->flag ^= (fdatas->flag & FLAG_NUMBERSIGN)
							? FLAG_NUMBERSIGN : FLAG_ZERO;
	}
	if (specifier == 'X')
	{
		i = 0;
		while (str[i])
		{
			str[i] = (char)ft_toupper(str[i]);
			i++;
		}
	}
	len = ft_strlen(str);
	fdatas->precision = fdatas->precision - len;
	fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
	fdatas->width = fdatas->width - fdatas->precision - len;
	if (fdatas->flag & FLAG_NUMBERSIGN)
	{
		fdatas->width -= 2;
		if (fdatas->flag & FLAG_ZERO)
			fdatas->bcount += write(1, (specifier == 'x') ? "0x" : "0X", 2);
	}
	if (fdatas->flag & FLAG_LESS)
	{
		if (fdatas->flag & FLAG_NUMBERSIGN && !(fdatas->flag & FLAG_ZERO))
			fdatas->bcount += write(1, (specifier == 'x') ? "0x" : "0X", 2);
		justify(str, fdatas);
	}

	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE || fdatas->flag & FLAG_SPACE)
													|| fdatas->width > 1)
			fdatas->bcount += write(1, &fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
	{
		if (fdatas->flag & FLAG_NUMBERSIGN && !(fdatas->flag & FLAG_ZERO))
			fdatas->bcount += write(1, (specifier == 'x') ? "0x" : "0X", 2);
		justify(str, fdatas);
	}
	ft_strdel(&str);
}
