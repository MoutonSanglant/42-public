/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_victory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/28 11:01:01 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/28 12:14:26 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puissance4.h"

static int		count_connections(t_grid *game, char *token,
									t_vec2 pos, t_vec2 dir)
{
	char	*p;
	int		x;
	int		y;

	if (dir.x == 0 && dir.y == 0)
		return (0);
	x = pos.x + dir.x;
	y = pos.y + dir.y;
	if (x >= game->col || x < 0
		|| y >= game->lin || y < 0)
		return (0);
	p = &game->grid[y][x];
	if (*p == *token)
	{
		game->state++;
		return (count_connections(game, token, vector2(x, y), dir));
	}
	return (game->state);
}

static int		check_token_at(t_grid *game, int i, int j)
{
	char	*p;
	int		k;

	p = &game->grid[i][j];
	if (*p == PLAYER_TOKEN || *p == AI_TOKEN)
	{
		k = -1;
		while (k < 2)
		{
			game->state = 0;
			if (count_connections(game, p, vector2(j, i), vector2(-1, k)) >= 3)
				return (1);
			game->state = 0;
			if (count_connections(game, p, vector2(j, i), vector2(0, k)) >= 3)
				return (1);
			game->state = 0;
			if (count_connections(game, p, vector2(j, i), vector2(1, k)) >= 3)
				return (1);
			k++;
		}
	}
	return (0);
}

void			check_victory(t_grid *game)
{
	int		i;
	int		j;
	int		check;

	i = 0;
	check = 0;
	while (i < game->lin)
	{
		j = 0;
		while (j < game->col)
		{
			game->state = check_token_at(game, i, j);
			if (game->state)
				return ;
			j++;
		}
		i++;
	}
}
