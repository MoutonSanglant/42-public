/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 15:08:07 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/23 16:18:27 by tdefresn         ###   ########.fr       */
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
	char			*str;
	unsigned int	unb;
	char			c;
	int				nb;
	int				offset;

	str = NULL;
	offset = 0;
	get_format_datas(format, fdatas, &offset);
	fdatas->specifier = format[offset];
//	ft_printf_format(format, fdatas);

	if (fdatas->specifier == 's')
		ft_print_formated_string(ap, fdatas);
	else if (fdatas->specifier == 'p')
	{
		str = va_arg(ap, char *);
		fdatas->bcount += (str) ? ft_putstr(str) : ft_putstr("0x0");
	}
	else if (fdatas->specifier == 'i')
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
	}
	else if (fdatas->specifier == 'd')
	{
		nb = va_arg(ap, int);
		if (fdatas->flag & FLAG_MORE && nb > 0)
			fdatas->bcount += write(1, "+", 1);
		else if (fdatas->flag & FLAG_SPACE)
			fdatas->bcount += write(1, " ", 1);
		fdatas->bcount += ft_putnbr(nb);
	}
	else if (fdatas->specifier == 'o')
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

		if (fdatas->flag & FLAG_NUMBERSIGN)
			ft_strprepend(&str, "0");
		nb = va_arg(ap, int);
		str = ft_itoa_base(nb, 8);
		fdatas->bcount += ft_putstr(str);
		ft_strdel(&str);
	}
	else if (fdatas->specifier == 'u')
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
	}
	else if (fdatas->specifier == 'x' || fdatas->specifier == 'X')
	{
		if (fdatas->length == LENGTH_NONE)
			str = ft_uitoa_base((uintmax_t)va_arg(ap, unsigned int), 16);
		else if (fdatas->length == LENGTH_HH)
			str = ft_uitoa_base((uintmax_t)va_arg(ap, unsigned int), 16);
		else if (fdatas->length == LENGTH_H)
			str = ft_uitoa_base((uintmax_t)va_arg(ap, unsigned int), 16);
		else if (fdatas->length == LENGTH_L)
			str = ft_uitoa_base((uintmax_t)va_arg(ap, unsigned long int), 16);
		else if (fdatas->length == LENGTH_LL)
			str = ft_uitoa_base((uintmax_t)va_arg(ap, unsigned long long int), 16);
		else if (fdatas->length == LENGTH_J)
			str = ft_uitoa_base((uintmax_t)va_arg(ap, uintmax_t), 16);
		else if (fdatas->length == LENGTH_Z)
			str = ft_uitoa_base((uintmax_t)va_arg(ap, size_t), 16);

		if (str[0] == '0')
		{
			if (fdatas->precision == 0)
				str[0] = '\0';
			fdatas->flag ^= (fdatas->flag & FLAG_NUMBERSIGN) ? FLAG_NUMBERSIGN : FLAG_ZERO;
		}
		if (fdatas->specifier == 'X')
		{
			int i = 0;

			while (str[i])
			{
				str[i] = (char)ft_toupper(str[i]);
				i++;
			}
		}

		fdatas->precision = fdatas->precision - ft_strlen(str);
		fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
		fdatas->width = fdatas->width - fdatas->precision - ft_strlen(str);
		if (fdatas->flag & FLAG_NUMBERSIGN)
		{
			fdatas->width -= 2;
			if (fdatas->flag & FLAG_ZERO)
				fdatas->bcount += write(1, (fdatas->specifier == 'x') ? "0x" : "0X", 2);
		}
		if (fdatas->flag & FLAG_LESS)
		{
			if (fdatas->flag & FLAG_NUMBERSIGN && !(fdatas->flag & FLAG_ZERO))
				fdatas->bcount += write(1, (fdatas->specifier == 'x') ? "0x" : "0X", 2);
			justify(str, fdatas);
		}

		while (fdatas->width > 0)
		{
			if (!(fdatas->flag & FLAG_MORE || fdatas->flag & FLAG_SPACE) || fdatas->width > 1)
				fdatas->bcount += write(1, &fdatas->fill_char, 1);
			fdatas->width--;
		}
		if (!(fdatas->flag & FLAG_LESS))
		{
			if (fdatas->flag & FLAG_NUMBERSIGN && !(fdatas->flag & FLAG_ZERO))
				fdatas->bcount += write(1, (fdatas->specifier == 'x') ? "0x" : "0X", 2);
			justify(str, fdatas);
		}

		//fdatas->bcount += ft_putstr(str);
		ft_strdel(&str);
	}
	else if (fdatas->specifier == 'c')
	{
		if (fdatas->length == LENGTH_NONE)
			c = va_arg(ap, int);
		else if (fdatas->length == LENGTH_L)
			c = (wint_t)va_arg(ap, wint_t);
		c = (char)va_arg(ap, int);
		ft_putchar(c);
		fdatas->bcount++;
	}
	else
	{
		//va_arg(ap, void *);
		//fdatas->precision = fdatas->precision;
		//fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
		//fdatas->width = fdatas->width - fdatas->precision;

		fdatas->flag ^= (fdatas->flag & FLAG_SPACE) ? FLAG_SPACE : FLAG_NONE;
		fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
		if (fdatas->flag & FLAG_LESS)
			justify("%", fdatas);
		fdatas->width--;
		while (fdatas->width > 0)
		{
			if (!(fdatas->flag & FLAG_MORE) || fdatas->width > 1)
				fdatas->bcount += write(1, &fdatas->fill_char, 1);
			fdatas->width--;
		}
		if (!(fdatas->flag & FLAG_LESS))
			justify("%", fdatas);
		//if (fdatas->flag & FLAG_SPACE)
		//	fdatas->bcount++;
		//fdatas->bcount += write(1, "%", 1);
	}

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
