/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:07:37 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/29 10:51:11 by tdefresn         ###   ########.fr       */
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
	fdatas->bcount += write(1, str, fdatas->precision);
}

void			ft_print_formated_string(va_list ap, t_fdata *fdatas)
{
	char	*str;
	char	*s;

	str = NULL;
	if (fdatas->length == LENGTH_NONE)
		str = va_arg(ap, char *);
//	else if (fdatas->length == LENGTH_L)
//		str = (wchar_t *)va_arg(ap, wchar_t *);
	if (!str)
		s = ft_strdup("(null)");
	else
		s = ft_strdup(str);
	fdatas->precision = (fdatas->precision >= 0)
							? fdatas->precision : (int)ft_strlen(s);
	fdatas->precision = ((size_t)fdatas->precision < ft_strlen(s))
							? fdatas->precision : (int)ft_strlen(s);
	fdatas->width = fdatas->width - fdatas->precision;
	if (fdatas->flag & FLAG_LESS)
		justify(s, fdatas);
	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE || fdatas->flag & FLAG_SPACE)
													|| fdatas->width > 1)
			fdatas->bcount += write(1, &fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		justify(s, fdatas);
	ft_strdel(&s);
}
