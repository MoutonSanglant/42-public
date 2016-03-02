/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_pointer.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:49:08 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/02 21:00:08 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_print_formated_pointer(va_list ap, t_fdata *fdatas)
{
	char	*str;
	char	*s;
	char	*join;

	str = va_arg(ap, char *);
	if (str)
		s = ft_itoa_base((uintptr_t)str, 16);
	else if (fdatas->precision == 0)
		s = ft_strdup("");
	else
		s = ft_strdup("0");
	fdatas->precision -= ft_strlen(s) + 1;
	while (fdatas->precision >= 0)
	{
		join = ft_strjoin("0", s);
		ft_strdel(&s);
		s = join;
		fdatas->precision--;
	}
	join = ft_strjoin("0x", s);
	ft_print_formated_string(ap, fdatas, join);
	ft_strdel(&s);
	ft_strdel(&join);
}
