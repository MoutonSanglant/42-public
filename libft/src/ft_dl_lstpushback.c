/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstpushback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 16:31:17 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:30:20 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_dl_lstpushback(t_dl_list *lst, t_dl_list *new)
{
	t_dl_list	*last;

	if (!lst || !new)
	{
		ft_putendl("ft_dl_lstpushback error:\nsent parameter is NULL.");
		return ;
	}
	last = ft_dl_lstback(lst);
	last->next = new;
	new->prev = last;
}

#else

void	ft_dl_lstpushback(t_dl_list *lst, t_dl_list *new)
{
	t_dl_list	*last;

	last = ft_dl_lstback(lst);
	last->next = new;
	new->prev = last;
}
#endif
