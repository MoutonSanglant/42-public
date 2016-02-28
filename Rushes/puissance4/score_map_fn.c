/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_map_fn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 15:35:17 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/28 12:21:27 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puissance4.h"

/*
**	Return an empty score map where border are weigthed
**	according to the rule: the closest is the worst
*/

int		**new_score_map(int width, int height)
{
	int		**score_map;
	int		score;
	int		i;
	int		j;

	score_map = (int **)ft_memalloc(sizeof(int *) * height);
	i = 0;
	while (i < height)
	{
		score_map[i] = (int *)ft_memalloc(sizeof(int) * width);
		j = 0;
		while (j < width)
		{
			score = 0;
			if (j < 3)
				score = j - 3;
			else if (width - j < 3)
				score = (width - j) - 3;
			score_map[i][j] = score;
			j++;
		}
		i++;
	}
	return (score_map);
}

void	destroy_score_map(int **score_map, int height)
{
	int		i;

	i = 0;
	while (i < height)
	{
		ft_memdel((void **)&score_map[i]);
		i++;
	}
	ft_memdel((void *)&score_map);
}
