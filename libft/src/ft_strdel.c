/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:33:25 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 03:36:11 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_strdel(char **as)
{
	if (!as)
	{
		ft_putendl("ft_strdel returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	if (!*as)
	{
		ft_putendl("ft_strdel returned the following error:\n\
					free candidate is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	free(*as);
	*as = NULL;
}

#else

void	ft_strdel(char **as)
{
	free(*as);
	*as = NULL;
}
#endif
