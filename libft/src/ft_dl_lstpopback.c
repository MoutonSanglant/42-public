/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstpopback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 17:03:25 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 19:42:43 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_dl_lstpopback(t_dl_list **alst)
{
	t_dl_list	*last;

	if (!alst)
	{
		ft_putendl("ft_dl_lstpopback error:\nsent parameter is NULL.");
		return ;
	}
	if (!*alst)
	{
		ft_putendl("ft_dl_lstpopback error:\n candidate for free is NULL.");
		return ;
	}
	last = ft_dl_lstback(*alst);
	if (last->prev)
	{
		last->prev->next = NULL;
		ft_memdel((void *)&last);
	}
	else
		ft_dl_lstclear(alst);
}

#else

void	ft_dl_lstpopback(t_dl_list **alst)
{
	t_dl_list	*last;

	last = ft_dl_lstback(*alst);
	if (last->prev)
	{
		last->prev->next = NULL;
		ft_memdel((void *)&last);
	}
	else
		ft_dl_lstclear(alst);
}
#endif
