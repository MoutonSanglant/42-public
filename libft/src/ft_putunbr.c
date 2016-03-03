/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 19:39:29 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/16 00:52:32 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	printnbr(unsigned int n, int *bcount)
{
	if (n >= 10)
		printnbr(n / 10, bcount);
	ft_putchar((n % 10) + '0');
	(*bcount)++;
}

int		ft_putunbr(unsigned int n)
{
	int bcount;

	bcount = 0;
	printnbr(n, &bcount);
	return (bcount);
}
