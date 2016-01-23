/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstpushback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 16:31:17 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/14 11:51:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_lstpushback(t_dl_list *lst, t_dl_list *new)
{
	t_dl_list	*last;

	last = ft_dl_lstback(lst);
	last->next = new;
	new->prev = last;
}
