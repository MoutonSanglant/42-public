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

static int		ft_putwchar(wint_t *wi)
{
	wint_t	z;

	char *str;
	int len;
	int count;
	count = 0;

	*wi = L'α';
	str = ft_itoa_base(*wi, 2);
	len = ft_strlen(str);

	printf("\nC: %C\n", *wi);
	//ft_putchar('@');
	//ft_putstr(ft_itoa_base(*wi, 2));
	ft_putchar('\n');
	ft_putchar('w');
	ft_putchar('\n');
	ft_putstr(str);
	ft_putchar('\n');
	ft_putstr("len: ");
	ft_putnbr(len);
	ft_putchar('\n');

	ft_putchar('h');
	ft_putchar('\n');
	unsigned char *h;
	h = (unsigned char *)wi;
	ft_putstr(ft_itoa_base(*h, 2));
	ft_putchar('\n');
	ft_putstr(ft_itoa_base(*(h + 1), 2));
	ft_putchar('\n');
	//ft_putchar('M');
	//ft_putstr(ft_itoa_base(MASK_2B, 2));
	//ft_putchar('\n');
	if (len <= 7)
		return (write(1, wi, 1));
	else if (len <= 11)
	{
		int i;
		/*ft_putchar('\n');
		ft_putchar('i');
		ft_putchar('\n');
		ft_putstr(ft_itoa_base(i, 2));
		ft_putchar('\n');*/
		// Write left part, applying mask
		i = ((((*h & 0b11000000) >> 6) |((*(h + 1) << 2) & 0b00011111)) | 0b11000000);
		count += write(1, &i, 1);
		/*ft_putchar('\n');
		ft_putchar('i');
		ft_putchar('\n');
		ft_putstr(ft_itoa_base(i, 2));
		ft_putchar('\n');*/
		// Write right part
		i = ((*h & 0b00111111) | 0b10000000);
		count += write(1, &i, 1);
		//z &= 0b0001111100111111;
		return (count);
	}
	else if (len <= 16)
	{
		z = *wi;
		z &= 0b000111110011111100111111;
		return (write(1, &z, 3));
	}
	else
	{
		z = *wi;
		z &= 0b00011111001111110011111100111111;
		return (write(1, &z, 4));
	}
//	ft_putnbr(MASK_4B);
//	ft_putchar('\n');
	(void)wi;
	//return (0);
	return (write(1, "@", 1));
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
