/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queuepush.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 21:22:37 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_queuepush(t_queue *queue, t_queue *new)
{
	t_queue	*last;

	if (!queue || !new)
	{
		ft_putendl("ft_queuepush returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	last = ft_queueback(queue);
	last->next = new;
	new->prev = last;
}

#else

void	ft_queuepush(t_queue *queue, t_queue *new)
{
	t_queue	*last;

	last = ft_queueback(queue);
	last->next = new;
	new->prev = last;
}
#endif
