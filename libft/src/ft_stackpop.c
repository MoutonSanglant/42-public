/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackpop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:28 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/05 23:52:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_stackpop(t_stack **astack)
{
	t_stack	*top;

	if (!astack)
	{
		ERROR_PARAM("ft_stackpop");
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
