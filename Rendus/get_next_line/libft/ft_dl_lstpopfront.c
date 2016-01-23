/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstpopfront.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 16:49:57 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/14 11:51:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
