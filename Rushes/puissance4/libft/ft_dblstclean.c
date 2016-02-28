/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstclean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 15:32:15 by gdruel            #+#    #+#             */
/*   Updated: 2015/03/23 15:37:56 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_dblstclean(t_dblist *lst)
{
	t_dblist	*it;
	t_dblist	*next;

	it = lst->next;
	while (it != lst)
	{
		next = it->next;
		free(it);
		it = next;
	}
}
