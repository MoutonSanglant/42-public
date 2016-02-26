/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 15:08:07 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/26 23:01:34 by tdefresn         ###   ########.fr       */
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

/*
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
*/

/*
**	.precision:
**	d i o u x X
**
**	s max character printed
*/

static const char		*get_format_datas(const char *format, const char *specifier, t_fdata *fdatas)
{
	fdatas->flag = FLAG_NONE;
	fdatas->width = 0;
	fdatas->precision = -1;
	fdatas->length = LENGTH_NONE;
	while (format < specifier)
	{
		if (*format == '-')
			fdatas->flag |= FLAG_LESS;
		else if (*format == '+')
			fdatas->flag |= FLAG_MORE;
		else if (*format == ' ')
			fdatas->flag |= FLAG_SPACE;
		else if (*format == '#')
			fdatas->flag |= FLAG_NUMBERSIGN;
		else if (*format == '0')
			fdatas->flag |= FLAG_ZERO;
		else if (*format == '.')
		{
			format++;
			fdatas->precision = ft_atoi(format);
			while (ft_isdigit(*format))
				format++;
			format--;
		}
		else if (ft_isdigit(*format))
		{
			fdatas->width = ft_atoi(format);
			while (ft_isdigit(*format))
				format++;
			format--;
		}
		else if (*format == 'h')
			fdatas->length |= (*(format + 1) == 'h' && format++) ? LENGTH_HH : LENGTH_H;
		else if (*format == 'l')
			fdatas->length |= (*(++format + 1) == 'l' && format++) ? LENGTH_LL : LENGTH_L;
		else if (*format == 'j')
			fdatas->length |= LENGTH_J;
		else if (*format == 'z')
			fdatas->length |= LENGTH_Z;
		else
		{
			specifier = format;
			break;
		}
		format++;
	}
	fdatas->fill_char = (fdatas->flag & FLAG_ZERO && !(fdatas->flag & FLAG_LESS)) ? '0' : ' ';
	return (specifier);
}

static const char		*read_arg(va_list ap, const char *format, t_fdata *fdatas)
{
	const char	*specifier;

	if (!(specifier = ft_strpbrk(format, "sSpdDioOuUxXcC%")))
		specifier = get_format_datas(format, format + ft_strlen(format), fdatas);
	else
		specifier = get_format_datas(format, specifier, fdatas);
//	if (!specifier)
//		return (0);
	if (ft_strpbrk(specifier, "SDOUC"))
		fdatas->length = LENGTH_L;
	if (*specifier == 's' || *specifier == 'S')
		ft_print_formated_string(ap, fdatas);
	else if (*specifier == 'p')
		ft_print_formated_pointer(ap, fdatas);
	else if (*specifier == 'i' || *specifier == 'd' || *specifier == 'D')
		ft_print_formated_digit(ap, fdatas);
	else if (*specifier == 'o' || *specifier == 'O')
		ft_print_formated_octal(ap, fdatas);
	else if (*specifier == 'u' || *specifier == 'U')
		ft_print_formated_unsigned(ap, fdatas);
	else if (*specifier == 'x' || *specifier == 'X')
		ft_print_formated_hex(ap, fdatas, *specifier);
	else if (*specifier == 'c' || *specifier == 'C')
		ft_print_formated_char(ap, fdatas);
	else
		ft_print_formated_space(specifier, fdatas);

	return (specifier);
}

int				ft_printf(const char * restrict format, ...)
{
	const char	*from_ptr;
	const char	*to_ptr;
	va_list		ap;
	t_fdata		fdatas;

	fdatas.bcount = 0;
	va_start(ap, format);
	from_ptr = format;
	while ((to_ptr = ft_strchr(from_ptr, '%')))
	{
		fdatas.bcount += write(1, from_ptr, (to_ptr - from_ptr));
		to_ptr = read_arg(ap, (to_ptr + 1), &fdatas) + 1;
		if (fdatas.flag == FLAG_FORMAT_ERROR)
			return (fdatas.bcount);
		from_ptr = to_ptr;
	}
	fdatas.bcount += write(1, from_ptr, ft_strlen(from_ptr));
	va_end(ap);
	return (fdatas.bcount);
}
