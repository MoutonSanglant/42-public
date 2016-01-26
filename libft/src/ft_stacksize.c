/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacksize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:04:44 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

int		ft_stacksize(t_stack *stack)
{
	t_stack		*top;
	int			i;

	if (!stack)
	{
		ft_putendl("ft_stacksize returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (-1);
	}
	top = stack;
	i = 0;
	while (top->prev)
	{
		top = top->prev;
		i++;
	}
	return (i);
}

#else

int		ft_stacksize(t_stack *stack)
{
	t_stack		*top;
	int			i;

	top = stack;
	i = 0;
	while (top->prev)
	{
		top = top->prev;
		i++;
	}
	return (i);
}
#endif
