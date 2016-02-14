/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queuefront.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:09 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 21:18:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

t_queue		*ft_queuefront(t_queue *queue)
{
	if (!queue)
	{
		ft_putendl("ft_queuefront returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (NULL);
	}
	if (queue->prev)
		return (ft_queuefront(queue->prev));
	return (queue);
}

#else

t_queue		*ft_queuefront(t_queue *queue)
{
	if (queue->prev)
		return (ft_queuefront(queue->prev));
	return (queue);
}
#endif
