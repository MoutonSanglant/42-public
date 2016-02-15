/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 15:08:07 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/15 22:01:33 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

enum printflag {
	NONE = 0x0,
	MINUS_SIGN = 0x1,
	MORE_SIGN = 0x2,
	SPACE = 0x4,
	NUMBER_SIGN = 0x8,
	ZERO = 0x10 };

/*
**	printf is formated such as
**	%[flags][width][.precision][length]specifier
*/

/*
**	flags matching table
**	sS: -
**	p: -
**	cC: -
**	xX: - # 0
**	uU: - 0
**	oO: - # 0
**	i: + - 0 {space}
**	dD: + - 0 {space}
*/

/*
**	flags:
**	'-'
**	'+' works with i, d and D
**	' ' is ignored when '+' present
**	'#'
**		used with o, x or X specifiers
**		-> print '0', '0x' or '0X' before the number
**		used with a, A, e, E, f, F, g, G
**		-> force the output to contain a digital point,
**			even when none is necessary
**	'0' left pad the number with zeroes
**		is ignored when '-' present
*/

static int		get_flags(const char *arg_type_str, int *offset)
{
	enum printflag	flag;

	flag = 0;
	if (arg_type_str[*offset] == '-' && ++(*offset))
		flag |= MINUS_SIGN | get_flags(arg_type_str, offset);
	else if (arg_type_str[*offset] == '+' && ++(*offset))
		flag |= MORE_SIGN | get_flags(arg_type_str, offset);
	else if (arg_type_str[*offset] == ' ' && ++(*offset))
		flag |= SPACE | get_flags(arg_type_str, offset);
	else if (arg_type_str[*offset] == '#' && ++(*offset))
		flag |= NUMBER_SIGN | get_flags(arg_type_str, offset);
	else if (arg_type_str[*offset] == '0' && ++(*offset))
		flag |= ZERO | get_flags(arg_type_str, offset);
	else
		return (0);

	return (flag);
}

static int		read_arg(va_list ap, const char *arg_type_str)
{
	int				offset;
	enum printflag	flag;
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
	offset = 0;
	flag = get_flags(arg_type_str, &offset);

	if (arg_type_str[offset] == 's')
	{
		char *str;
		str = va_arg(ap, char *);
		ft_putstr(str);
		offset++;
	}
	else if (arg_type_str[offset] == 'p')
	{
		char *str;
		str = va_arg(ap, char *);
		ft_putaddr(str);
		offset++;
	}
	else if (arg_type_str[offset] == 'i')
	{
		int nb;
		nb = va_arg(ap, int);
		if (flag & MORE_SIGN && nb > 0)
			write(1, "+", 1);
		else if (flag & SPACE)
			write(1, " ", 1);
		ft_putnbr(nb);
		offset++;
	}
	else if (arg_type_str[offset] == 'd')
	{
		int nb;
		nb = va_arg(ap, int);
		if (flag & MORE_SIGN && nb > 0)
			write(1, "+", 1);
		else if (flag & SPACE)
			write(1, " ", 1);
		ft_putnbr(nb);
		offset++;
	}
	else if (arg_type_str[offset] == 'o')
	{
		int nb;
		char *str;

		nb = va_arg(ap, int);
		str = ft_itoa_base(nb, 8);
		ft_putstr(str);
		ft_strdel(&str);
		offset++;
	}
	else if (arg_type_str[offset] == 'u')
	{
		unsigned int nb;
		nb = va_arg(ap, unsigned int);
		ft_putunbr(nb);
		offset++;
	}
	else if (arg_type_str[offset] == 'x')
	{
		int nb;
		char *str;
		//ft_putstr("0x");
		nb = va_arg(ap, int);
		str = ft_itoa_base(nb, 16);
		ft_putstr(str);
		ft_strdel(&str);
		offset++;
	}
	else if (arg_type_str[offset] == 'c')
	{
		char c;
		c = (char)va_arg(ap, int);
		ft_putchar(c);
		offset++;
	}
	else
		va_arg(ap, void *);

	return (offset);
}

int				ft_printf(const char * restrict format, ...)
{
	va_list		ap;
	int			i;
	int			from_idx;
	int			to_idx;
	int			length;

	va_start(ap, format);
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
			from_idx = i + 1 + read_arg(ap, &format[i + 1]);
		}
		to_idx = ++i;
	}
	length = to_idx - from_idx;
	write(1, &format[from_idx], length);
	va_end(ap);
	return (0);
}
