/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queuepop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:16 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 21:20:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_queuepop(t_queue **aqueue)
{
	t_queue	*first;

	if (!aqueue)
	{
		ft_putendl("ft_queuepop returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	if (!*aqueue)
	{
		ft_putendl("ft_queuepop returned the following error:\n\
					free candidate is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
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

#else

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
#endif
