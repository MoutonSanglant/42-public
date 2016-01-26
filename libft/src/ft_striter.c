/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:34:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:36:20 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef DEBUG

# include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	if (!s || !f)
	{
		ft_putendl("ft_striter returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	while (*s)
		f(s++);
}

#else

void	ft_striter(char *s, void (*f)(char *))
{
	while (*s)
		f(s++);
}
#endif
