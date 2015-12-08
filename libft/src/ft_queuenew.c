/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queuenew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:12 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/08 14:44:13 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_queue		*ft_queuenew(void const *content, size_t content_size)
{
	t_queue *queue;

	queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	if (queue)
	{
		if (content)
		{
			queue->content = ft_memalloc(content_size);
			queue->content = ft_memcpy(queue->content, content, content_size);
			queue->content_size = content_size;
		}
		else
		{
			queue->content = NULL;
			queue->content_size = 0;
		}
		queue->next = NULL;
		queue->prev = NULL;
	}
	return (queue);
}
