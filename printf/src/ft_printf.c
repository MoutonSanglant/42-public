/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 15:08:07 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/26 17:03:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

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

static t_fflag		get_flags(const char *format, int *offset)
{
	t_fflag		flag;

	flag = 0;
	if (format[*offset] == '-' && ++(*offset))
		flag |= FLAG_LESS | get_flags(format, offset);
	else if (format[*offset] == '+' && ++(*offset))
		flag |= FLAG_MORE | get_flags(format, offset);
	else if (format[*offset] == ' ' && ++(*offset))
		flag |= FLAG_SPACE | get_flags(format, offset);
	else if (format[*offset] == '#' && ++(*offset))
		flag |= FLAG_NUMBERSIGN | get_flags(format, offset);
	else if (format[*offset] == '0' && ++(*offset))
		flag |= FLAG_ZERO | get_flags(format, offset);
	return (flag);
}

/*
**	.precision:
**	d i o u x X
**
**	s max character printed
*/

static void		get_format_datas(const char *format, t_fdata *fdatas, int *offset)
{
	fdatas->flag = get_flags(format, offset);
	fdatas->fill_char = (fdatas->flag & FLAG_ZERO && !(fdatas->flag & FLAG_LESS)) ? '0' : ' ';
	fdatas->width = ft_atoi(&format[*offset]);
	while (ft_isdigit(format[*offset]))
		(*offset)++;
	fdatas->precision = -1;
	if (format[*offset] == '.' && ++(*offset))
	{
		fdatas->precision = ft_atoi(&format[*offset]);
		while (ft_isdigit(format[*offset]))
			(*offset)++;
	}
	fdatas->length = LENGTH_NONE;
	if (format[*offset] == 'h')
		fdatas->length = (format[*offset + 1] == 'h') ? LENGTH_HH : LENGTH_H;
	else if (format[*offset] == 'l')
		fdatas->length = (format[*offset + 1] == 'l') ? LENGTH_LL : LENGTH_L;
	else if (format[*offset] == 'j')
		fdatas->length = LENGTH_J;
	else if (format[*offset] == 'z')
		fdatas->length = LENGTH_Z;
	if (fdatas->length != LENGTH_NONE)
		(*offset)++;
	if (fdatas->length == LENGTH_HH || fdatas->length == LENGTH_LL)
		(*offset)++;
}

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
static int		read_arg(va_list ap, const char *format, t_fdata *fdatas)
{
	int		offset;
	char	specifier;

	offset = 0;
	get_format_datas(format, fdatas, &offset);
	fdatas->specifier = format[offset];

	specifier = fdatas->specifier;
	if (specifier == 'D' || specifier == 'O' || specifier == 'U' || specifier == 'C' || specifier == 'S')
		fdatas->length = LENGTH_L;
	if (specifier == 's' || specifier == 'S')
		ft_print_formated_string(ap, fdatas);
	else if (specifier == 'p')
		ft_print_formated_pointer(ap, fdatas);
	else if (specifier == 'i' || specifier == 'd' || specifier == 'D')
		ft_print_formated_digit(ap, fdatas);
	else if (specifier == 'o' || specifier == 'O')
		ft_print_formated_octal(ap, fdatas);
	else if (specifier == 'u' || specifier == 'U')
		ft_print_formated_unsigned(ap, fdatas);
	else if (specifier == 'x' || specifier == 'X')
		ft_print_formated_hex(ap, fdatas);
	else if (specifier == 'c' || specifier == 'C')
		ft_print_formated_char(ap, fdatas);
	else
		ft_print_formated_space(fdatas);

	return (++offset);
}

int				ft_printf(const char * restrict format, ...)
{
	va_list		ap;
	int			i;
	int			from_idx;
	int			to_idx;
	int			length;
	t_fdata		fdatas;

	i = 0;
	to_idx = 0;
	from_idx = 0;
	fdatas.bcount = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			length = to_idx - from_idx;
			if (length > 0)
				fdatas.bcount += write(1, &format[from_idx], length);
			i += read_arg(ap, &format[i + 1], &fdatas);
			from_idx = i + 1;
		}
		to_idx = ++i;
	}
	length = to_idx - from_idx;
	if (length > 0)
		fdatas.bcount += write(1, &format[from_idx], length);
	va_end(ap);
	return (fdatas.bcount);
}
