/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 03:34:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_memdel(void **ap)
{
	if (!ap)
	{
		ft_putendl("ft_memdel returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	if (!*ap)
	{
		ft_putendl("ft_memdel returned the following error:\n\
					free candidate is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	free(*ap);
	*ap = NULL;
}

#else

void	ft_memdel(void **ap)
{
	free(*ap);
	*ap = NULL;
}
#endif
