/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 16:28:38 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 19:31:25 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_dl_lstiter(t_dl_list *lst, void (*f)(t_dl_list *elem))
{
	if (!lst || !f)
	{
		ft_putendl("ft_dl_lstiter error:\nsent parameter is NULL.");
		return ;
	}
	f(lst);
	if (lst->next)
		ft_dl_lstiter(lst->next, f);
}

#else

void	ft_dl_lstiter(t_dl_list *lst, void (*f)(t_dl_list *elem))
{
	f(lst);
	if (lst->next)
		ft_dl_lstiter(lst->next, f);
}
#endif
