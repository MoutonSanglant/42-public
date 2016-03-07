/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 15:08:07 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/07 19:27:51 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
**	printf format usage
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
**	.precision:
**	d i o u x X
**	s max character printed
*/

static int			get_precision_width_length(const char **f, t_fdata *d)
{
	if (**f == '.' && (*f += 1))
	{
		d->precision = ft_atoi(*f);
		while (ft_isdigit(**f))
			*f += 1;
		*f -= 1;
	}
	else if (ft_isdigit(**f))
	{
		d->width = ft_atoi(*f);
		while (ft_isdigit(**f))
			*f += 1;
		*f -= 1;
	}
	else if (**f == 'h')
		d->length |= (*(*f + 1) == 'h' && (*f += 1)) ? LENGTH_HH : LENGTH_H;
	else if (**f == 'l')
		d->length |= (*(*f + 1) == 'l' && (*f += 1)) ? LENGTH_LL : LENGTH_L;
	else if (**f == 'j')
		d->length |= LENGTH_J;
	else if (**f == 'z')
		d->length |= LENGTH_Z;
	else
		return (0);
	return (1);
}

static const char	*get_format_datas(const char *format,
									const char *specifier, t_fdata *d)
{
	d->flag = FLAG_NONE;
	d->width = 0;
	d->precision = -1;
	d->length = LENGTH_NONE;
	while (format < specifier)
	{
		if (*format == '-')
			d->flag |= FLAG_LESS;
		else if (*format == '+')
			d->flag |= FLAG_MORE;
		else if (*format == ' ')
			d->flag |= FLAG_SPACE;
		else if (*format == '#')
			d->flag |= FLAG_NUMBERSIGN;
		else if (*format == '0')
			d->flag |= FLAG_ZERO;
		else if (!get_precision_width_length(&format, d))
		{
			specifier = format;
			break ;
		}
		format++;
	}
	d->fill_char = (d->flag & FLAG_ZERO && !(d->flag & FLAG_LESS)) ? '0' : ' ';
	return (specifier);
}

static int			is_long(const char *spec)
{
	char	*str;

	str = ft_strnew(1);
	str[0] = spec[0];
	str[1] = '\0';
	if (ft_strpbrk(str, "SDOUC"))
	{
		ft_strdel(&str);
		return (1);
	}
	ft_strdel(&str);
	return (0);
}

static const char	*read_arg(va_list ap,
									const char *format, t_fdata *fdatas)
{
	const char	*spec;

	if (!(spec = ft_strpbrk(format, "sSpdDioOuUxXcC%")))
		spec = get_format_datas(format, format + ft_strlen(format), fdatas);
	else
		spec = get_format_datas(format, spec, fdatas);
	if (is_long(spec))
		fdatas->length = LENGTH_L;
	if (*spec == 's' || *spec == 'S')
		ft_print_formated_string(ap, fdatas, NULL);
	else if (*spec == 'p')
		ft_print_formated_pointer(ap, fdatas);
	else if (*spec == 'i' || *spec == 'd' || *spec == 'D')
		ft_print_formated_digit(ap, fdatas);
	else if (*spec == 'o' || *spec == 'O')
		ft_print_formated_octal(ap, fdatas);
	else if (*spec == 'u' || *spec == 'U')
		ft_print_formated_unsigned(ap, fdatas);
	else if (*spec == 'x' || *spec == 'X')
		ft_print_formated_hex(ap, fdatas, *spec);
	else if (*spec == 'c' || *spec == 'C')
		ft_print_formated_char(ap, fdatas);
	else
		ft_print_formated_space(spec, fdatas);
	return (spec);
}

int					ft_printf(const char *restrict format, ...)
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
		if (fdatas.flag & FLAG_FORMAT_ERROR)
			return (fdatas.bcount);
		from_ptr = to_ptr;
	}
	fdatas.bcount += write(1, from_ptr, ft_strlen(from_ptr));
	va_end(ap);
	return (fdatas.bcount);
}
