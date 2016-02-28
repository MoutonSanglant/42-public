/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstdelhead.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 17:16:09 by gdruel            #+#    #+#             */
/*   Updated: 2015/03/24 17:16:54 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dblstdelhead(t_dblist *root)
{
	if (root->next != root)
		ft_dblstdelone(root->next);
}
