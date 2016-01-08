/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/08 01:19:26 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memdel(void **ap)
{
#ifdef DEBUG
	if (!*ap)
	{
		ft_putendl("Error: freeing a NULL pointer, check your code !!");
		return ;
	}
#endif
	free(*ap);
	*ap = NULL;
}
