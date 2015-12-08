/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackpop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:28 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/08 14:45:11 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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
