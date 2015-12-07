/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 16:42:36 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/07 17:40:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_dl_list	*ft_dl_lstback(t_dl_list *lst)
{
	if (lst->next)
		return (ft_dl_lstback(lst->next));
	return (lst);
}
