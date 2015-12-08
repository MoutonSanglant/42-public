/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queueback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:43:55 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/08 14:43:56 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_queue		*ft_queueback(t_queue *queue)
{
	if (queue->next)
		return (ft_queueback(queue->next));
	return (queue);
}
