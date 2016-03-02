/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:07:37 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/02 04:23:08 by tdefresn         ###   ########.fr       */
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

static void		print_formated_string(t_fdata *fdatas, char *str)
{
	int		len;

	len = ft_strlen(str);
	fdatas->precision = (fdatas->precision >= 0) ? fdatas->precision : len;
	fdatas->precision = (fdatas->precision < len) ? fdatas->precision : len;
	fdatas->width = fdatas->width - fdatas->precision;
	if (fdatas->flag & FLAG_LESS)
		justify(str, fdatas);
	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE || fdatas->flag & FLAG_SPACE)
													|| fdatas->width > 1)
			fdatas->bcount += write(1, &fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		justify(str, fdatas);
}

static void		justify_long_string(wchar_t *wstr, t_fdata *fdatas)
{
	int		r_bytes;
	int		w_bytes;

	r_bytes = -1;
	w_bytes = 0;
	while(wstr[++r_bytes])
	{
		if (wstr[r_bytes] < (1 << 7))
			w_bytes += 1;
		else if (wstr[r_bytes] < (1 << 11))
			w_bytes += 2;
		else
			w_bytes += 3;
		if (w_bytes <= fdatas->precision)
			fdatas->bcount += ft_putwchar(&wstr[r_bytes]);
		else
			break ;
	}
}

/*
**	Issue: not justifying correctly when precision is specified
**	with a large value...
*/

static void		print_formated_long_string(t_fdata *fdatas, wchar_t *wstr)
{
	int		r_bytes;
	int		w_bytes;
	int		noprec;

	noprec = 1;
	if (fdatas->precision > 0)
		noprec = 0;
	fdatas->precision = (fdatas->precision >= 0) ? fdatas->precision : INT_MAX;
	r_bytes = -1;
	w_bytes = 0;
	while (wstr[++r_bytes])
	{
		if (wstr[r_bytes] < (1 << 7))
			w_bytes += 1;
		else if (wstr[r_bytes] < (1 << 11))
			w_bytes += 2;
		else
			w_bytes += 3;
		if (w_bytes > fdatas->precision)
			break ;
	}
	r_bytes--;
	if (fdatas->flag & FLAG_LESS)
		justify_long_string(wstr, fdatas);
	fdatas->width = (fdatas->width > 0) ? fdatas->width : 0;
	if (noprec)
		fdatas->width -= w_bytes;
	else
		fdatas->width += r_bytes - fdatas->precision;
	while (fdatas->width-- > 0)
		fdatas->bcount += write(1, " ", 1);
	if (!(fdatas->flag & FLAG_LESS))
		justify_long_string(wstr, fdatas);
}

void			ft_print_formated_string(va_list ap, t_fdata *fdatas)
{
	wchar_t		*wstr;
	char		*str;

	str = NULL;
	wstr = NULL;
	if (fdatas->length == LENGTH_NONE)
		str = va_arg(ap, char *);
	else if (fdatas->length == LENGTH_L)
		wstr = (wchar_t *)va_arg(ap, wchar_t *);
	if (!str && !wstr)
	{
		fdatas->precision = (fdatas->precision < 0) ? 7 : fdatas->precision;
		if (fdatas->precision < 6)
			str = ft_strdup(" ");
		else
			str = ft_strdup("(null)");
		print_formated_string(fdatas, str);
		ft_strdel(&str);
	}
	else if (str)
		print_formated_string(fdatas, str);
	else
		print_formated_long_string(fdatas, wstr);
}
