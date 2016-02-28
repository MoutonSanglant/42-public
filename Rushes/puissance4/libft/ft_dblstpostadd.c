/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstpostadd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 16:16:50 by gdruel            #+#    #+#             */
/*   Updated: 2015/03/24 16:32:01 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_dblstpostadd(t_dblist *elem, int val)
{
	t_dblist *new;

	new = malloc(sizeof(*new));
	if (new != NULL)
	{
		new->val = val;
		new->prev = elem;
		new->next = elem->next;
		elem->next->prev = new;
		elem->next = new;
	}
}
