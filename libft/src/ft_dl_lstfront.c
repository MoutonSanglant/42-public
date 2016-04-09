/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstfront.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 16:40:03 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/07 17:32:40 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_dl_list	*ft_dl_lstfront(t_dl_list *lst)
{
	if (lst->prev)
		return (ft_dl_lstfront(lst->prev));

	return (lst);
}
