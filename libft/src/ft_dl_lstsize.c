/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 17:15:03 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:30:43 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

int		ft_dl_lstsize(t_dl_list *lst)
{
	t_dl_list	*first;
	int			i;

	if (!lst)
	{
		ft_putendl("ft_dl_lstsize error:\nsent parameter is NULL.");
		return (-1);
	}
	first = ft_dl_lstfront(lst);
	i = 0;
	while (first->next)
	{
		first = first->next;
		i++;
	}
	return (i);
}

#else

int		ft_dl_lstsize(t_dl_list *lst)
{
	t_dl_list	*first;
	int			i;

	first = ft_dl_lstfront(lst);
	i = 0;
	while (first->next)
	{
		first = first->next;
		i++;
	}
	return (i);
}
#endif
