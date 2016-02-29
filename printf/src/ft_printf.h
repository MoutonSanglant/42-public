/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 20:23:04 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/18 20:23:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <wchar.h>
# include <stdarg.h>

typedef enum	e_fflag
{
	FLAG_NONE = 0x0,
	FLAG_LESS = 0x1,
	FLAG_MORE = 0x2,
	FLAG_SPACE = 0x4,
	FLAG_NUMBERSIGN = 0x8,
	FLAG_ZERO = 0x10,
	FLAG_FORMAT_ERROR = 0x20
}				t_fflag;

typedef enum	e_flength
{
	LENGTH_NONE = 0x0,
	LENGTH_HH = 0x1,
	LENGTH_H = 0x2,
	LENGTH_L = 0x4,
	LENGTH_LL = 0x8,
	LENGTH_J = 0x10,
	LENGTH_Z = 0x20
}				t_flength;

typedef struct	s_fdata
{
	const char	*format;
	t_fflag		flag;
	t_flength	length;
	int			width;
	int			precision;
	int			bcount;
	char		fill_char;
}				t_fdata;

void			ft_print_formated_char(va_list ap, t_fdata *fdatas);
void			ft_print_formated_string(va_list ap, t_fdata *fdatas);
void			ft_print_formated_pointer(va_list ap, t_fdata *fdatas);
void			ft_print_formated_digit(va_list ap, t_fdata *fdatas);
void			ft_print_formated_octal(va_list ap, t_fdata *fdatas);
void			ft_print_formated_hex(va_list ap, t_fdata *fdatas,
															char specifier);
void			ft_print_formated_unsigned(va_list ap, t_fdata *fdatas);
void			ft_print_formated_space(const char *format, t_fdata *fdatas);

#endif
