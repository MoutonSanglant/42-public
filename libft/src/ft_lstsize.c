/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 17:14:37 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 19:57:48 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

int		ft_lstsize(t_list *lst)
{
	int		i;

	if (!lst)
	{
		ft_putendl("ft_lstsize returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (-1);
	}
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

#else

int		ft_lstsize(t_list *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
#endif
