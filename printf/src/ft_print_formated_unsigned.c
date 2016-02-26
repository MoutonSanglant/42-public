/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_unsigned.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:41:18 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/26 03:03:41 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		justify_left(t_fdata *fdatas, char *str)
{
	while (fdatas->precision-- > 0)
		fdatas->bcount += write(1, "0", 1);
	fdatas->bcount += ft_putstr(str);
	while (fdatas->width-- > 0)
		fdatas->bcount += write(1, &fdatas->fill_char, 1);
}

static void		justify_right(t_fdata *fdatas, char *str)
{
	if (fdatas->flag & FLAG_ZERO)
	{
		if ((fdatas->flag & FLAG_SPACE))
		{
			fdatas->bcount += write(1, " ", 1);
			fdatas->width--;
		}
		while (fdatas->width-- > 0)
			fdatas->bcount += write(1, &fdatas->fill_char, 1);
	}
	else
	{
		if ((fdatas->flag & FLAG_SPACE))
		{
			fdatas->bcount += write(1, " ", 1);
			fdatas->width--;
		}
		while (fdatas->width-- > 0)
			fdatas->bcount += write(1, &fdatas->fill_char, 1);
	}
	while (fdatas->precision-- > 0)
		fdatas->bcount += write(1, "0", 1);
	fdatas->bcount += ft_putstr(str);
}

static char		*str_from_arg(va_list ap, t_fdata *fdatas)
{
	if (fdatas->length == LENGTH_NONE)
		return (ft_uitoa((unsigned int)va_arg(ap, unsigned int)));
	else if (fdatas->length == LENGTH_HH)
		return (ft_uitoa((unsigned char)va_arg(ap, unsigned int)));
	else if (fdatas->length == LENGTH_H)
		return (ft_uitoa((unsigned short int)va_arg(ap, unsigned int)));
	else if (fdatas->length == LENGTH_L)
		return (ft_uitoa((unsigned long int)va_arg(ap, unsigned long int)));
	else if (fdatas->length == LENGTH_LL)
		return (ft_uitoa((unsigned long long int)va_arg(ap, unsigned long long int)));
	else if (fdatas->length == LENGTH_J)
		return (ft_uitoa((uintmax_t)va_arg(ap, uintmax_t)));
	else if (fdatas->length == LENGTH_Z)
		return(ft_uitoa((size_t)va_arg(ap, size_t)));
	return (NULL);
}

void	ft_print_formated_unsigned(va_list ap, t_fdata *fdatas)
{
	char			*str;
	int				len;

	str = str_from_arg(ap, fdatas);

	if (str[0] == '0' && fdatas->precision == 0)
		str[0] = '\0';
	if (fdatas->precision >= 0)
		fdatas->fill_char = ' ';
	len = ft_strlen(str);
	fdatas->precision = fdatas->precision - len;
	fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
	fdatas->width = fdatas->width - fdatas->precision - len;
	if (fdatas->flag & FLAG_LESS)
		justify_left(fdatas, str);
	else
		justify_right(fdatas, str);
	ft_strdel(&str);
}
