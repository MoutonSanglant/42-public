/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 10:30:18 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 19:42:12 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (!alst || !new)
	{
		ft_putendl("ft_lstadd error:\nsent parameter is NULL.");
		return ;
	}
	if (!*alst)
	{
		ft_putendl("ft_lstadd error:\n candidate for free is NULL.");
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
