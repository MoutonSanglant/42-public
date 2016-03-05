/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 10:30:18 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/05 20:19:10 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (!alst || !new)
	{
		ERROR_PARAM("ft_lstadd");
		return ;
	}
	if (!*alst)
	{
		ERROR_FREE("ft_lstadd");
		return ;
	}
	new->next = *alst;
	*alst = new;
}

#else

void	ft_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}
#endif
