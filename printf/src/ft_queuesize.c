/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queuesize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 21:22:09 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

int		ft_queuesize(t_queue *queue)
{
	t_queue		*first;
	int			i;

	if (!queue)
	{
		ft_putendl("ft_queuesize returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (-1);
	}
	first = ft_queuefront(queue);
	i = 0;
	while (first->next)
	{
		first = first->next;
		i++;
	}
	return (i);
}

#else

int		ft_queuesize(t_queue *queue)
{
	t_queue		*first;
	int			i;

	first = ft_queuefront(queue);
	i = 0;
	while (first->next)
	{
		first = first->next;
		i++;
	}
	return (i);
}
#endif
