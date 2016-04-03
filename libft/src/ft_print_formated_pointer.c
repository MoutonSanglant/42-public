/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_pointer.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:49:08 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/24 14:54:42 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		remove_extra_flags(t_fdata *fdatas)
{
	fdatas->flag ^= (fdatas->flag & FLAG_SPACE) ? FLAG_SPACE : FLAG_NONE;
	fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	if (fdatas->flag & FLAG_ZERO)
		fdatas->flag |= FLAG_LESS;
}

void			ft_print_formated_pointer(va_list *ap, t_fdata *fdatas)
{
	char	*str;
	char	*s;
	char	*join;

	str = va_arg(*ap, char *);
	if (str)
		s = ft_itoa_base((uintptr_t)str, 16);
	else if (fdatas->precision == 0)
		s = ft_strdup("");
	else
		s = ft_strdup("0");
	remove_extra_flags(fdatas);
	fdatas->precision -= ft_strlen(s) + 1;
	while (fdatas->precision >= 0)
	{
		join = ft_strjoin("0", s);
		ft_strdel(&s);
		s = join;
		fdatas->precision--;
		fdatas->width--;
	}
	join = ft_strjoin("0x", s);
	ft_print_formated_string(ap, fdatas, join);
	ft_strdel(&s);
	ft_strdel(&join);
}
