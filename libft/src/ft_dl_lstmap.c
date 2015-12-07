/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 16:30:01 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/07 17:40:43 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_dl_list		*ft_dl_lstmap(t_dl_list *lst, t_dl_list *(*f)(t_dl_list *elem))
{
	t_dl_list	*new_list;

	new_list = f(lst);
	if (new_list)
	{
		if (lst->next)
		{
			new_list->next = ft_dl_lstmap(lst->next, f);
			if (!new_list->next)
			{
				free(new_list);
				new_list = NULL;
			}
		}
	}
	return (new_list);
}
