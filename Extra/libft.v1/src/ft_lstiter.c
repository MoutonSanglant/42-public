/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 10:48:21 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 19:57:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (!lst || !f)
	{
		ft_putendl("ft_lstiter returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	f(lst);
	if (lst->next)
		ft_lstiter(lst->next, f);
}

#else

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	f(lst);
	if (lst->next)
		ft_lstiter(lst->next, f);
}
#endif
