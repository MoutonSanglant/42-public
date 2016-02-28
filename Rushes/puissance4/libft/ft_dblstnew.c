/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 15:08:47 by gdruel            #+#    #+#             */
/*   Updated: 2015/08/17 15:00:29 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_dblist*ft_dblstnew(void)
{
	t_dblist *root;

	root = malloc(sizeof(*root));
	if (root != NULL)
	{
		root->prev = root;
		root->next = root;
	}
	return (root);
}
