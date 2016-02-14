/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 14:34:40 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:31:34 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

t_list			*ft_lstgetat(t_list *lst, int idx)
{
	if (!lst)
	{
		ft_putendl("ft_lstgetat returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (NULL);
	}
	while (idx > 0)
	{
		lst = lst->next;
		if (!lst)
			break ;
		idx--;
	}
	return (lst);
}

#else

t_list			*ft_lstgetat(t_list *lst, int idx)
{
	while (idx > 0)
	{
		lst = lst->next;
		if (!lst)
			break ;
		idx--;
	}
	return (lst);
}
#endif
