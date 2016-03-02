/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:45:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/02 00:08:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		justify(wint_t *c, t_fdata *fdatas)
{
	if (fdatas->flag & FLAG_SPACE)
		fdatas->bcount += write(1, " ", 1);
	if (fdatas->length == LENGTH_L)
		fdatas->bcount += ft_putwchar((wchar_t *)c);
	else
		fdatas->bcount += write(1, (char *)c, 1);
}

static int		unicode_length(wint_t c)
{
	if (c < (1 << 11))
		return (1);
	else if (c < (1 << 16))
		return (2);
	return (1);
}

void			ft_print_formated_char(va_list ap, t_fdata *fdatas)
{
	wint_t	c;

	c = 0;
	if (fdatas->length == LENGTH_NONE)
		c = va_arg(ap, int);
	else if (fdatas->length == LENGTH_L)
	{
		c = (wint_t)va_arg(ap, wint_t);
		fdatas->width -= unicode_length(c);
	}
	fdatas->flag ^= (fdatas->flag & FLAG_SPACE) ? FLAG_SPACE : FLAG_NONE;
	fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	if (fdatas->flag & FLAG_LESS)
		justify(&c, fdatas);
	fdatas->width--;
	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE) || fdatas->width > 1)
			fdatas->bcount += write(1, &fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		justify(&c, fdatas);
}
