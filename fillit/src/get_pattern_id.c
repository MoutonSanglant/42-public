/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pattern_id.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/12 14:15:20 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/19 11:33:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	get_pattern_id(t_mask16 mask)
{
	int	i;
	int	j;

	i = 0;
	while (i < 19)
	{
		j = 0;
		while (j < 9)
		{
			if (g_mask_table[i][j] == mask)
				return (i);
			j++;
		}
		i++;
	}
	error();
	return (-1);
}
