/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 00:57:09 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/14 15:25:49 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nbr_length_in_base(uint64_t n, size_t base)
{
	size_t		i;

	i = 0;
	while (n != 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

static char		*to_base(uint64_t value, size_t base)
{
	char		*str;
	size_t		l;

	l = nbr_length_in_base(value, base);
	str = ft_strnew(sizeof(char) * l);
	str[l] = '\0';
	while (l > 0)
	{
		l--;
		str[l] = value % base;
		value /= base;
		str[l] += '0';
		if (str[l] > '9')
			str[l] += 'a' - 10 - '0';
	}
	return (str);
}

char			*ft_itoa_base(int64_t value, int base)
{
	char	*str;

	str = NULL;
	if (value == 0)
		str = ft_strdup("0");
	else if (base < 2 || base > 16)
		str = NULL;
	else if (base == 10)
		str = ft_itoa(value);
	else
		str = to_base((uint64_t)value, (size_t)base);
	return (str);
}
