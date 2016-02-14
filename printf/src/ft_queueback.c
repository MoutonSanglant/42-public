/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queueback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:43:55 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 21:17:21 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

t_queue		*ft_queueback(t_queue *queue)
{
	if (!queue)
	{
		ft_putendl("ft_queueback returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (NULL);
	}
	if (queue->next)
		return (ft_queueback(queue->next));
	return (queue);
}

#else

t_queue		*ft_queueback(t_queue *queue)
{
	if (queue->next)
		return (ft_queueback(queue->next));
	return (queue);
}
#endif
