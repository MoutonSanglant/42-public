/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queuepush.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:19 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/14 11:51:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_queuepush(t_queue *queue, t_queue *new)
{
	t_queue	*last;

	last = ft_queueback(queue);
	last->next = new;
	new->prev = last;
}
