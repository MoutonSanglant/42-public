/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/14 14:33:45 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_memdel(void **ap)
{
	if (!*ap)
	{
		ft_putendl("Error: freeing a NULL pointer, check your code !!");
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
