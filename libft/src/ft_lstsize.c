/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 17:14:37 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/07 17:31:16 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_lstsize(t_list *lst)
{
	t_list	*first;
	int i;

	first = lst;
	i = 0;
	while (first->next)
	{
		first = first->next;
		i++;
	}
	return (i);
}
