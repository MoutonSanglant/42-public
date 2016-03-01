/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:45:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/01 01:27:25 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

#define MASK_1B 0b10000000 // 0xxx xxxx
#define MASK_UN 0b01000000
#define MASK_2B 0b00100000 // 110x xxxx 10xxxxxx
#define MASK_3B 0b00010000 // 1110 xxxx 10xxxxxx 10xxxxxx
#define MASK_4B 0b00001000 // 1111 0xxx 10xxxxxx 10xxxxxx 10xxxxxx

#include <stdio.h>

//	h
// xxxxxxx
// |0xxxxxxx|
//	h+1		h
// yyy|yyxxxxxx|
// |110yyyyy|10xxxxxx|
//	h+1			h
// |zzzzyyyy|yyxxxxxx|
// |1110zzzz|10yyyyyy|10xxxxxx|
//	h+2		h+1		h
// wwwzz|zzzzyyyy|yyxxxxxx|
// |11110www|10zzzzzz|10yyyyyy|10xxxxxx|

static int		ft_putwchar(wint_t *wi)
{
	unsigned char	*h;
	char			*str;
	int				i;
	int				len;

	//*wi = L'α';
	str = ft_itoa_base(*wi, 2);
	//ft_putendl("wi:");
	//ft_putstr(str);
	//ft_putchar('\n');
	len = ft_strlen(str);
	ft_strdel(&str);
	h = (unsigned char *)wi;
	if (len <= 7)
		return (write(1, wi, 1));
	else if (len <= 11)
	{
		i = ((((*h & 0b11000000) >> 6) | ((*(h + 1) << 2) & 0b00011111)) | 0b11000000);
		write(1, &i, 1);
		// Write right part
		i = ((*h & 0b00111111) | 0b10000000);
		write(1, &i, 1);
		return (2);
	}
	else if (len <= 16)
	{
		i = (((*(h + 1) & 0b11110000) >> 4) | 0b11100000);
		write(1, &i, 1);
		i = ((((*h & 0b11000000) >> 6) | ((*(h + 1) << 2) & 0b00111111)) | 0b10000000);
		write(1, &i, 1);
		i = ((*h & 0b00111111) | 0b10000000);
		write(1, &i, 1);
		return (3);
	}
	i = (((*(h + 2) & 0b00011100) >> 2) | 0b11110000);
	write(1, &i, 1);
	i = ((((*(h + 1) & 0b11110000) >> 4) | ((*(h + 2) << 4) & 0b00111111)) | 0b10000000);
	write(1, &i, 1);
	i = ((((*h & 0b11000000) >> 6) | ((*(h + 1) << 2) & 0b00111111)) | 0b10000000);
	write(1, &i, 1);
	i = ((*h & 0b00111111) | 0b10000000);
	write(1, &i, 1);
	return (4);
}

static void		justify(wint_t *wi, t_fdata *fdatas)
{
	if (fdatas->flag & FLAG_SPACE)
		fdatas->bcount += write(1, " ", 1);
	if (fdatas->length == LENGTH_L)
		fdatas->bcount += ft_putwchar(wi);
	else
		fdatas->bcount += write(1, (char *)wi, 1);
}

void			ft_print_formated_char(va_list ap, t_fdata *fdatas)
{
	wint_t	wi;
	//char	c;

	//c = 0;
	//wi = NULL;
	wi = 0;
	if (fdatas->length == LENGTH_NONE)
		wi = va_arg(ap, int);
	else if (fdatas->length == LENGTH_L)
		wi = (wint_t)va_arg(ap, wint_t);
	fdatas->flag ^= (fdatas->flag & FLAG_SPACE) ? FLAG_SPACE : FLAG_NONE;
	fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	if (fdatas->flag & FLAG_LESS)
		justify(&wi, fdatas);
	fdatas->width--;
	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE) || fdatas->width > 1)
			fdatas->bcount += write(1, &fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		justify(&wi, fdatas);
}
