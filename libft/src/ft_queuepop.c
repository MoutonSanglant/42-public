/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queuepop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:16 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/08 14:44:17 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_queuepop(t_queue **aqueue)
{
	t_queue	*first;

	first = ft_queuefront(*aqueue);
	if (first->next)
	{
		*aqueue = first->next;
		(*aqueue)->prev = NULL;
		ft_memdel((void *)&first);
	}
	else
		ft_memdel((void **)aqueue);
}
