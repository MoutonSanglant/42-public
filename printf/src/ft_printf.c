/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 15:08:07 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/18 22:28:35 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include <stdarg.h>

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
	fdatas->fill_char = (fdatas->flag & FLAG_ZERO) ? '0' : ' ';
	fdatas->width = ft_atoi(&format[*offset]);
	while (ft_isdigit(format[*offset]))
		(*offset)++;
	fdatas->precision = 0;
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
	while (fdatas->precision-- > 0)
		fdatas->bcount += write(1, "0", 1);
	fdatas->bcount += ft_putstr(str);
}

static int		read_arg(va_list ap, const char *format, t_fdata *fdatas)
{
	char			*str;
	unsigned int	unb;
	char			c;
	int				nb;
	int				offset;

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
	str = NULL;
	offset = 0;
	get_format_datas(format, fdatas, &offset);
//	ft_printf_format(format, fdatas);

	if (format[offset] == 's')
	{
		if (fdatas->length == LENGTH_NONE)
			str = va_arg(ap, char *);
	//	else if (fdatas->length == LENGTH_L)
	//		str = (wchar_t *)va_arg(ap, wchar_t *);
		fdatas->bcount += (str) ? ft_putstr(str) : ft_putstr("(null)");
		offset++;
	}
	else if (format[offset] == 'p')
	{
		str = va_arg(ap, char *);
		fdatas->bcount += (str) ? ft_putstr(str) : ft_putstr("0x0");
		offset++;
	}
	else if (format[offset] == 'i')
	{
		if (fdatas->length == LENGTH_NONE)
			str = ft_itoa(va_arg(ap, int));
		else if (fdatas->length == LENGTH_HH)
			str = ft_itoa((signed char)va_arg(ap, int));
		else if (fdatas->length == LENGTH_H)
			str = ft_itoa((short int)va_arg(ap, int));
		else if (fdatas->length == LENGTH_L)
			str = ft_imaxtoa((long int)va_arg(ap, long int));
		else if (fdatas->length == LENGTH_LL)
			str = ft_imaxtoa((long long int)va_arg(ap, long long int));
		else if (fdatas->length == LENGTH_J)
			str = ft_imaxtoa((intmax_t)va_arg(ap, intmax_t));
		else if (fdatas->length == LENGTH_Z)
			str = ft_imaxtoa((size_t)va_arg(ap, size_t));
		fdatas->precision = fdatas->precision - ft_strlen(str);
		fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
		fdatas->width = fdatas->width - fdatas->precision - ft_strlen(str);
		if (fdatas->flag & FLAG_LESS)
			justify(str, fdatas);
		while (fdatas->width > 0)
		{
			if (!(fdatas->flag & FLAG_MORE || fdatas->flag & FLAG_SPACE) || fdatas->width > 1)
				fdatas->bcount += write(1, &fdatas->fill_char, 1);
			fdatas->width--;
		}
		if (!(fdatas->flag & FLAG_LESS))
			justify(str, fdatas);
		ft_strdel(&str);
		offset++;
	}
	else if (format[offset] == 'd')
	{
		nb = va_arg(ap, int);
		if (fdatas->flag & FLAG_MORE && nb > 0)
			fdatas->bcount += write(1, "+", 1);
		else if (fdatas->flag & FLAG_SPACE)
			fdatas->bcount += write(1, " ", 1);
		fdatas->bcount += ft_putnbr(nb);
		offset++;
	}
	else if (format[offset] == 'o')
	{
		if (fdatas->length == LENGTH_NONE)
			str = ft_uitoa(va_arg(ap, unsigned int));
		else if (fdatas->length == LENGTH_HH)
			str = ft_uitoa((unsigned char)va_arg(ap, unsigned int));
		else if (fdatas->length == LENGTH_H)
			str = ft_uitoa((unsigned short int)va_arg(ap, unsigned int));
		else if (fdatas->length == LENGTH_L)
			str = ft_uimaxtoa((unsigned long int)va_arg(ap, unsigned long int));
		else if (fdatas->length == LENGTH_LL)
			str = ft_uimaxtoa((unsigned long long int)va_arg(ap, unsigned long long int));
		else if (fdatas->length == LENGTH_J)
			str = ft_uimaxtoa((uintmax_t)va_arg(ap, uintmax_t));
		else if (fdatas->length == LENGTH_Z)
			str = ft_uimaxtoa((size_t)va_arg(ap, size_t));

		nb = va_arg(ap, int);
		str = ft_itoa_base(nb, 8);
		fdatas->bcount += ft_putstr(str);
		ft_strdel(&str);
		offset++;
	}
	else if (format[offset] == 'u')
	{
		if (fdatas->length == LENGTH_NONE)
			str = ft_uitoa(va_arg(ap, unsigned int));
		else if (fdatas->length == LENGTH_HH)
			str = ft_uitoa((unsigned char)va_arg(ap, unsigned int));
		else if (fdatas->length == LENGTH_H)
			str = ft_uitoa((unsigned short int)va_arg(ap, unsigned int));
		else if (fdatas->length == LENGTH_L)
			str = ft_uimaxtoa((unsigned long int)va_arg(ap, unsigned long int));
		else if (fdatas->length == LENGTH_LL)
			str = ft_uimaxtoa((unsigned long long int)va_arg(ap, unsigned long long int));
		else if (fdatas->length == LENGTH_J)
			str = ft_uimaxtoa((uintmax_t)va_arg(ap, uintmax_t));
		else if (fdatas->length == LENGTH_Z)
			str = ft_uimaxtoa((size_t)va_arg(ap, size_t));

		unb = va_arg(ap, unsigned int);
		fdatas->bcount += ft_putunbr(unb);
		ft_strdel(&str);
		offset++;
	}
	else if (format[offset] == 'x')
	{
		if (fdatas->length == LENGTH_NONE)
			str = ft_uitoa(va_arg(ap, unsigned int));
		else if (fdatas->length == LENGTH_HH)
			str = ft_uitoa((unsigned char)va_arg(ap, unsigned int));
		else if (fdatas->length == LENGTH_H)
			str = ft_uitoa((unsigned short int)va_arg(ap, unsigned int));
		else if (fdatas->length == LENGTH_L)
			str = ft_uimaxtoa((unsigned long int)va_arg(ap, unsigned long int));
		else if (fdatas->length == LENGTH_LL)
			str = ft_uimaxtoa((unsigned long long int)va_arg(ap, unsigned long long int));
		else if (fdatas->length == LENGTH_J)
			str = ft_uimaxtoa((uintmax_t)va_arg(ap, uintmax_t));
		else if (fdatas->length == LENGTH_Z)
			str = ft_uimaxtoa((size_t)va_arg(ap, size_t));

		//bcount += ft_putstr("0x");
		nb = va_arg(ap, int);
		str = ft_itoa_base(nb, 16);
		fdatas->bcount += ft_putstr(str);
		ft_strdel(&str);
		offset++;
	}
	else if (format[offset] == 'X')
	{
		if (fdatas->length == LENGTH_NONE)
			str = ft_uitoa(va_arg(ap, unsigned int));
		else if (fdatas->length == LENGTH_HH)
			str = ft_uitoa((unsigned char)va_arg(ap, unsigned int));
		else if (fdatas->length == LENGTH_H)
			str = ft_uitoa((unsigned short int)va_arg(ap, unsigned int));
		else if (fdatas->length == LENGTH_L)
			str = ft_uimaxtoa((unsigned long int)va_arg(ap, unsigned long int));
		else if (fdatas->length == LENGTH_LL)
			str = ft_uimaxtoa((unsigned long long int)va_arg(ap, unsigned long long int));
		else if (fdatas->length == LENGTH_J)
			str = ft_uimaxtoa((uintmax_t)va_arg(ap, uintmax_t));
		else if (fdatas->length == LENGTH_Z)
			str = ft_uimaxtoa((size_t)va_arg(ap, size_t));

	}
	else if (format[offset] == 'c')
	{
		if (fdatas->length == LENGTH_NONE)
			c = va_arg(ap, int);
		else if (fdatas->length == LENGTH_L)
			c = (wint_t)va_arg(ap, wint_t);
		c = (char)va_arg(ap, int);
		ft_putchar(c);
		fdatas->bcount++;
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
	t_fdata		fdatas;

	i = 0;
	from_idx = 0;
	fdatas.bcount = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			length = to_idx - from_idx;
			fdatas.bcount += write(1, &format[from_idx], length);
			if (format[i + 1] == '%')
			{
				fdatas.bcount += write(1, "%", 1);
				i += 2;
				from_idx = i;
				continue;
			}
			from_idx = i + 1 + read_arg(ap, &format[i + 1], &fdatas);
		}
		to_idx = ++i;
	}
	length = to_idx - from_idx;
	if (length > 0)
		fdatas.bcount += write(1, &format[from_idx], length);
	va_end(ap);
	return (fdatas.bcount);
}
