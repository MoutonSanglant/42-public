/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 15:08:07 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/15 18:12:56 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

static int		read_arg(va_list arg_list, const char *arg_type_str)
{
	// Cases:
	// s   string of characters
	// S   's' with 'l' (ell) modifier
	// p   pointer adresse
	// dD  signed decimal integer
	// i   signed decimal integer
	// oO  unsigned octal
	// uU  unsigned decimal integer
	// xX  unsigned hexadecimal integer lowercase / uppercase
	// cC  character
	// C   's' with 'l' (ell) modifier
	if (arg_type_str[0] == 'i')
		va_arg(arg_list, int);
	else
		va_arg(arg_list, void *);

	return (0);
}

int				ft_printf(const char * restrict format, ...)
{
	va_list		arg_list;
	int			i;
	int			from_idx;
	int			to_idx;
	int			length;

	va_start(arg_list, format);
	i = 0;
	from_idx = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			length = to_idx - from_idx;
			write(1, &format[from_idx], length);
			if (format[i + 1] == '%')
			{
				write(1, "%", 1);
				i += 2;
				from_idx = i;
				continue;
			}
			read_arg(arg_list, &format[i + 1]);
			/*
			**	TODO
			**	from_idx must be i + length of readen type with the symbol
			**	(ie. %i is 2, %llu is 4, etc.)
			*/
			from_idx = i + 1;
		}
		to_idx = ++i;
	}
	length = to_idx - from_idx;
	write(1, &format[from_idx], length);
	va_end(arg_list);
	return (0);
}
