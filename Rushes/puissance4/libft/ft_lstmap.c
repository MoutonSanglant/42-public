/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 12:07:16 by gdruel            #+#    #+#             */
/*   Updated: 2015/03/06 16:11:58 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*temp;
	t_list	*ret;
	t_list	*fo;

	ret = NULL;
	if (lst != NULL)
	{
		temp = (*f)(lst);
		new = ft_lstnew(temp->content, temp->content_size);
		if (new == NULL)
			return (NULL);
		lst = lst->next;
		ret = new;
		while (lst)
		{
			temp = (*f)(lst);
			if ((fo = ft_lstnew(temp->content, temp->content_size)) == NULL)
				return (NULL);
			new->next = fo;
			lst = lst->next;
			new = new->next;
		}
	}
	return (ret);
}
