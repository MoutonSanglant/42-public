/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 10:30:36 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/03 13:50:59 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void		delelem(void *content, size_t content_size)
{
	if (content_size > 0)
		ft_memdel(&content);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*next;

	next = NULL;
	if (lst->next)
	{
		next = ft_lstmap(lst->next, f);
		if (!next)
			return (NULL);
	}
	//new_list = f(ft_lstnew(lst->content, lst->content_size));
	//new_list = (t_list *)malloc(sizeof(t_list));
	new_list = ft_lstnew(lst->content, lst->content_size);
	new_list = f(new_list);
	if (new_list)
	{
		if (next)
			ft_lstadd(&next, new_list);
	}
	else
	{
		if (next)
			ft_lstdel(&next, &delelem);
		
		return (NULL);
	}
	return (new_list);
}
