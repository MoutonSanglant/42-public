/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 19:52:19 by exam              #+#    #+#             */
/*   Updated: 2015/12/04 21:17:56 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		nbrlength(long long int n)
{
	int		length;

	if (n == 0)
		return (1);
	length = 0;
	while (n > 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

static char		getat(long long int n, int idx)
{
	char				c;
	int					i;
	long long int		lft;

	i = 0;
	while (i < idx)
	{
		n /= 10;
		i++;
	}
	lft = n;
	lft /= 10;
	lft *= 10;
	n = n - lft;
	c = n + '0';
	return (c);
}

char			*ft_itoa(int n)
{
	char			*str;
	int				size;
	int				sign;
	int				i;

	sign = 0;
	if (n < 0)
	{
		n *= -1;
		sign = 1;
	}
	size = nbrlength((long long int)n);
	str = malloc(sizeof(char) * (size + 1 + sign));
	if (str == NULL)
		return (NULL);
	i = sign;
	if (sign)
		str[0] = '-';
	while (i < size + sign)
	{
		str[i] = getat((long long int)n, (size - 1 + sign) - i);
		i++;
	}
	str[i] = '\0';
	return (str);
}
