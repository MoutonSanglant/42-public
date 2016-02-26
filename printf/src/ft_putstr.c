/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:49 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/26 20:45:31 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	NOTE
**	This is not the standard "ft_putstr" since
**	it returns a value when it shouldn't.
**	===================================
**	void	ft_putstr(char const *s)
*/

#ifdef DEBUG

int		ft_putstr(char const *s)
{
	if (!s)
	{
		ft_putendl("ft_putstr returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	return (write(1, s, ft_strlen(s)));
}

#else

int		ft_putstr(char const *s)
{
	return (write(1, s, ft_strlen(s)));
}
#endif
