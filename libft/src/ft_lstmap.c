/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 10:30:36 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/10 16:58:02 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;

	new_list = f(lst);
	if (new_list)
	{
		if (lst->next)
		{
			new_list->next = ft_lstmap(lst->next, f);
			if (!new_list->next)
			{
				if (new_list->content)
					ft_memdel((void **)&new_list->content);
				ft_memdel((void **)&new_list);
			}
		}
	}
	return (new_list);
}
