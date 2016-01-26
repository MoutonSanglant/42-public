/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:35:30 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:16:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

size_t	ft_strlen(char const *s)
{
	size_t	i;

	if (!s)
	{
		ft_putendl("ft_strlen returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (0);
	}
	i = 0;
	while (*s++ != '\0')
		i++;
	return (i);
}

#else

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (*s++ != '\0')
		i++;
	return (i);
}
#endif
