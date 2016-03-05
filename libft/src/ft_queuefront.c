/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queuefront.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:09 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/05 23:50:09 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

t_queue		*ft_queuefront(t_queue *queue)
{
	if (!queue)
	{
		ERROR_PARAM("ft_queuefront");
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
