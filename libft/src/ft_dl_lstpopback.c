/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstpopback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 17:03:25 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/07 17:08:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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
