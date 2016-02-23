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

typedef enum	e_fflag
{
	FLAG_NONE		= 0x0,
	FLAG_LESS		= 0x1,
	FLAG_MORE		= 0x2,
	FLAG_SPACE		= 0x4,
	FLAG_NUMBERSIGN	= 0x8,
	FLAG_ZERO		= 0x10
}				t_fflag;

typedef enum	e_flength
{
	LENGTH_NONE,
	LENGTH_HH,
	LENGTH_H,
	LENGTH_L,
	LENGTH_LL,
	LENGTH_J,
	LENGTH_Z
}				t_flength;


typedef struct	s_fdata
{
	const char	*format;
	t_fflag		flag;
	t_flength	length;
	int			width;
	int			precision;
	int			bcount;
	char		specifier;
	char		fill_char;
}				t_fdata;

#endif
