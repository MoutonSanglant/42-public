/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 19:37:37 by gdruel            #+#    #+#             */
/*   Updated: 2015/03/06 16:08:51 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

static	int		ft_intlen(int n)
{
	int				len;

	len = 1;
	if (n < 0)
		len++;
	while (n >= 10 || n <= -10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static	char	*ft_fullfilstr(char *s, int n, int len)
{
	s[len] = '\0';
	len--;
	while (n != 0 && len >= 0)
	{
		s[len] = -(n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (s);
}

static	char	*ft_n_is_zero(void)
{
	char	*str;

	str = (char *)malloc(sizeof(*str) * 2);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char			*ft_itoa(int n)
{
	char			*s;
	int				len;

	s = NULL;
	len = ft_intlen(n);
	if (n == 0)
		return (ft_n_is_zero());
	else if (n > 0)
	{
		s = (char *)malloc((sizeof(*s) * (len + 1)));
		if (!s)
			return (NULL);
		n = -n;
	}
	else if (n < 0)
	{
		s = (char *)malloc((sizeof(*s) * (len + 1)));
		if (!s)
			return (NULL);
		s[0] = '-';
	}
	return (ft_fullfilstr(s, n, len));
}
