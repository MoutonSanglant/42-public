/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstpreadd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 16:09:09 by gdruel            #+#    #+#             */
/*   Updated: 2015/03/24 16:32:11 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_dblstpreadd(t_dblist *elem, int val)
{
	t_dblist *new;

	new = malloc(sizeof(*new));
	if (new != NULL)
	{
		new->val = val;
		new->prev = elem->prev;
		new->next = elem;
		elem->prev->next = new;
		elem->prev = new;
	}
}
