/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 12:52:16 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/07 13:15:32 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	nbrlength(long long int n)
{
	size_t		length;

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

static char		getat(long long int n, size_t idx)
{
	char				c;
	size_t				i;
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
	int				sign;
	size_t			size;
	size_t			i;
	long long int	ln;

	ln = (long long int)n;
	sign = 0;
	if (ln < 0)
	{
		ln *= -1;
		sign = 1;
	}
	size = nbrlength(ln);
	str = malloc(sizeof(char) * (size + sign + 1));
	if (str == NULL)
		return (NULL);
	i = sign - 1;
	if (sign)
		str[0] = '-';
	while (++i < size + sign)
		str[i] = getat(ln, (size + sign - 1) - i);
	str[i] = '\0';
	return (str);
}
