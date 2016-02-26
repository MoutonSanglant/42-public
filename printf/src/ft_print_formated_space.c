/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_space.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:44:05 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/26 21:41:45 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		justify(char c, t_fdata *fdatas)
{
	if (fdatas->flag & FLAG_SPACE)
		fdatas->bcount += write(1, " ", 1);
	fdatas->bcount += write(1, &c, 1);
}

static int		format_error(const char *format, t_fdata *fdatas)
{
	char		*ptr;

	if (format[0] != '%')
	{
		if ((ptr = ft_strchr(format, '%')))
		{
			while (format != ptr)
			{
				fdatas->bcount += write(1, format, 1);
				format++;
			}
		}
		else
		{
			fdatas->bcount += ft_putstr(format);
			fdatas->flag = FLAG_FORMAT_ERROR;
		}
		return (1);
	}
	return (0);
}

void	ft_print_formated_space(const char *format, t_fdata *fdatas)
{
	if (format_error(format, fdatas))
		return ;
	fdatas->flag ^= (fdatas->flag & FLAG_SPACE) ? FLAG_SPACE : FLAG_NONE;
	fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	if (fdatas->flag & FLAG_LESS)
		justify('%', fdatas);
	fdatas->width--;
	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE) || fdatas->width > 1)
			fdatas->bcount += write(1, &fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		justify('%', fdatas);
}
