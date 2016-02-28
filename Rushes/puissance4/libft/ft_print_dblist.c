/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dblist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/09 09:56:04 by gdruel            #+#    #+#             */
/*   Updated: 2015/04/09 13:39:57 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_dblist(t_dblist *lst)
{
	t_dblist *elem;

	elem = lst->next;
	while (elem != lst)
	{
		ft_putnbr(elem->val);
		ft_putstr(" ");
		elem = elem->next;
	}
	ft_putendl("");
}
