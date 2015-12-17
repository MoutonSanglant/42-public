/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 14:34:40 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/17 14:37:13 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
