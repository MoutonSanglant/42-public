/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 19:52:19 by exam              #+#    #+#             */
/*   Updated: 2015/12/04 17:19:17 by tdefresn         ###   ########.fr       */
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
	long long int	nn;

	nn = n;
	sign = 0;
	if (n < 0)
	{
		nn *= -1;
		sign = 1;
	}
	size = nbrlength(nn);
	str = malloc(sizeof(char) * (size + 1 + sign));
	if (str == NULL)
		return (NULL);
	i = sign;
	if (sign)
		str[0] = '-';
	while (i < size + sign)
	{
		str[i] = getat(nn, (size - 1 + sign) - i);
		i++;
	}
	str[i] = '\0';
	return (str);
}
