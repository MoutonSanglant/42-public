/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstclear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:45:50 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 19:42:49 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_dl_lstclear(t_dl_list **alst)
{
	if (!alst)
	{
		ft_putendl("ft_dl_lstclear error:\nsent parameter is NULL.");
		return ;
	}
	if (!*alst)
	{
		ft_putendl("ft_dl_lstclear error:\n candidate for free is NULL.");
		return ;
	}
	if ((*alst)->next)
		ft_dl_lstclear(&(*alst)->next);
	ft_memdel((void **)alst);
}

#else

void	ft_dl_lstclear(t_dl_list **alst)
{
	if ((*alst)->next)
		ft_dl_lstclear(&(*alst)->next);
	ft_memdel((void **)alst);
}
#endif
