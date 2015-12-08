/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacksize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:33 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/08 14:45:20 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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
