/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 12:52:16 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/25 19:44:42 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nbr_length(int n)
{
	size_t		i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char			*str;
	size_t			sign;
	size_t			l;

	if (n == 0)
	{
		str = ft_strnew(sizeof(char) * 1);
		if (str)
			str[0] = '0';
		return (str);
	}
	sign = (n > 0) ? 0 : 1;
	l = nbr_length(n) + sign;
	if (!(str = ft_strnew(sizeof(char) * l)))
		return (NULL);
	str[l] = '\0';
	if (sign != 0)
		str[0] = '-';
	while (l-- > sign)
	{
		str[l] = (sign > 0) ? HEX_TABLE(-(n % 10)) : HEX_TABLE(n % 10);
		n /= 10;
	}
	return (str);
}
