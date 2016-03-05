/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 19:01:17 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/05 20:40:06 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsort(t_list *lst, int (*cmp)(void *, void *))
{
	t_list	*first;
	t_list	*next;
	t_list	*prev;

	first = lst;
	if (!lst->next)
		return (lst);
	while (1)
	{
		prev = first;
		lst = first;
		next = lst->next;
		while (next)
		{
			if (!cmp(lst->content, next->content))
				break ;
			lst = next;
			next = lst->next;
			if (!next)
				return (first);
		}
		lst = first;
		next = lst->next;
		while (next)
		{
			if (!cmp(lst->content, next->content))
			{
				if (lst == first)
					first = next;
				if (prev != lst)
					prev->next = next;
				lst->next = next->next;
				next->next = lst;
			}
			prev = lst;
			lst = next;
			next = lst->next;
		}
	}
	return (first);
}
