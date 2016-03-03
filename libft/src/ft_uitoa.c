/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 22:08:44 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/26 16:48:51 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nbr_length(uintmax_t n)
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

char			*ft_uitoa(uintmax_t n)
{
	char			*str;
	size_t			l;

	if (n == 0)
	{
		str = ft_strnew(sizeof(char) * 1);
		if (str)
			str[0] = '0';
		return (str);
	}
	l = nbr_length(n);
	if (!(str = ft_strnew(sizeof(char) * l)))
		return (NULL);
	str[l] = '\0';
	while (l-- > 0)
	{
		str[l] = HEX_TABLE(n % 10);
		n /= 10;
	}
	return (str);
}
