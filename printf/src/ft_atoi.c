/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 21:48:42 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 19:13:49 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

int		ft_atoi(char const *str)
{
	int		sign;
	int		r;

	if (!str)
	{
		ft_putendl("ft_atoi error:\nsent parameter is NULL.");
		return (0);
	}
	r = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (str[0] == '-')
	{
		sign = -1;
		str++;
	}
	else if (str[0] == '+')
		str++;
	while (ft_isdigit(*str))
	{
		r *= 10;
		r += (*str++ - '0');
	}
	return (r * sign);
}

#else

int		ft_atoi(char const *str)
{
	int		sign;
	int		r;

	r = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (str[0] == '-')
	{
		sign = -1;
		str++;
	}
	else if (str[0] == '+')
		str++;
	while (ft_isdigit(*str))
	{
		r *= 10;
		r += (*str - '0');
		str++;
	}
	return (r * sign);
}
#endif
