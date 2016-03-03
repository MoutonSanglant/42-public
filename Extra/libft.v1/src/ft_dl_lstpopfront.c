/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstpopfront.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 16:49:57 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 19:42:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_dl_lstpopfront(t_dl_list **alst)
{
	t_dl_list	*first;

	if (!alst)
	{
		ft_putendl("ft_dl_lstpopfront error:\nsent parameter is NULL.");
		return ;
	}
	if (!*alst)
	{
		ft_putendl("ft_dl_lstpopfront error:\n candidate for free is NULL.");
		return ;
	}
	first = ft_dl_lstfront(*alst);
	if (first->next)
	{
		*alst = first->next;
		(*alst)->prev = NULL;
		ft_memdel((void *)&first);
	}
	else
		ft_dl_lstclear(alst);
}

#else

void	ft_dl_lstpopfront(t_dl_list **alst)
{
	t_dl_list	*first;

	first = ft_dl_lstfront(*alst);
	if (first->next)
	{
		*alst = first->next;
		(*alst)->prev = NULL;
		ft_memdel((void *)&first);
	}
	else
		ft_dl_lstclear(alst);
}
#endif
