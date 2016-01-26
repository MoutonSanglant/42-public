/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackpush.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:31 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:04:28 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_stackpush(t_stack **astack, t_stack *new)
{
	if (!astack || !new)
	{
		ft_putendl("ft_stackpush returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	if (!*astack)
	{
		ft_putendl("ft_queuesize returned the following error:\n\
					free candidate is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	new->prev = *astack;
	*astack = new;
}

#else

void	ft_stackpush(t_stack **astack, t_stack *new)
{
	new->prev = *astack;
	*astack = new;
}
#endif
