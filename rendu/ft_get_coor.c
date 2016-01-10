/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_coor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuchwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 14:59:12 by mabuchwa          #+#    #+#             */
/*   Updated: 2016/01/10 03:11:59 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	ft_get_coor(char *buf, t_pos *tab, int nb_fig)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	c = 0;
	j = 0;
	while (i < nb_fig)
	{
		(tab + i)->nb_tetri = nb_fig;
		(tab + i)->letter = 'A' + i;
		i++;
	}
	i--;
	while (buf[c])
	{
		if (buf[c] == '#')
		{
			(tab + i)->x[j] = c % 5 + 1;
			(tab + i)->y[j] = c / 5 + 1;
			j++;
		}
		c++;
	}
}
