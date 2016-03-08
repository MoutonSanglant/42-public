/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 19:01:17 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/08 10:16:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsort(t_list *lst, int (*cmp)(void *, void *))
{
	t_list	*first;
	t_list	*next;
	t_list	*prev;
	int		sorted;

	sorted = 0;
	first = lst;
	while (!sorted)
	{
		sorted = 1;
		prev = first;
		lst = first;
		next = lst->next;
		while (lst->next) //lst->next
		{
			if (!cmp(lst->content, lst->next->content)) // lst->next
			{
				sorted = 0;
				if (lst == first)
					first = lst->next; // lst->next
				if (prev != lst)
					prev->next = lst->next; // lst->next
				lst->next = next->next; //lst->next
				next->next = lst; // lst->next
			}
			prev = lst;
			lst = next; // lst->next
			next = lst->next;
		}
	}
	return (first);
}
