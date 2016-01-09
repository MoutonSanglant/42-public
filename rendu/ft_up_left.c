/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_up_left.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuchwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 11:15:06 by mabuchwa          #+#    #+#             */
/*   Updated: 2016/01/06 17:07:27 by mabuchwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void		ft_move(t_pos *tab, int *i, int *result_x, int *result_y)
{
	int j;

	j = 0;
	while (j < 4)
	{
		(tab + *i)->x[j] = (((tab + *i)->x[j]) - (*result_x - 1)) - 1;
		(tab + *i)->y[j] = (((tab + *i)->y[j]) - (*result_y - 1)) - 1;
		j++;
	}
}

void			ft_up_left(t_pos *tab, int nb_fig)
{
	int j;
	int i;
	int result_x;
	int result_y;

	i = 0;
	while (i < nb_fig)
	{
		j = 0;
		result_x = 5;
		result_y = 5;
		while (j < 4)
		{
			if ((tab + i)->x[j] < result_x)
				result_x = (tab + i)->x[j];
			if ((tab + i)->y[j] < result_y)
				result_y = (tab + i)->y[j];
			j++;
		}
		if (result_x != 1)
			ft_move(tab, &i, &result_x, &result_y);
		i++;
	}
}
