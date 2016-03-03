/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackpop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:28 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:03:25 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_stackpop(t_stack **astack)
{
	t_stack	*top;

	if (!astack)
	{
		ft_putendl("ft_stackpop returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	top = *astack;
	if (top->prev)
	{
		*astack = top->prev;
		ft_memdel((void *)&top);
	}
	else
		ft_memdel((void **)astack);
}

#else

void	ft_stackpop(t_stack **astack)
{
	t_stack	*top;

	top = *astack;
	if (top->prev)
	{
		*astack = top->prev;
		ft_memdel((void *)&top);
	}
	else
		ft_memdel((void **)astack);
}
#endif
