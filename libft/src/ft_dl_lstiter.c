/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 16:28:38 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/14 11:47:07 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_lstiter(t_dl_list *lst, void (*f)(t_dl_list *elem))
{
	f(lst);
	if (lst->next)
		ft_dl_lstiter(lst->next, f);
}
