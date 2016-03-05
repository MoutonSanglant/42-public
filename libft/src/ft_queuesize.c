/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queuesize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/05 23:51:41 by tdefresn         ###   ########.fr       */
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
		ERROR_PARAM("ft_queuesize");
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
