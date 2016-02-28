/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_play_turn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 14:13:02 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/28 14:38:26 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puissance4.h"

/*
**	The last 2 rules:
**	1) boundaries proximity:
**		extend the vector to see if there is enough room
**		left for a full line. If no, set THREAT to ZERO
**	2) diagonals:
**		already checked, but the score must be discarded
**		if not directly accessible (check ground proximity)
**	3) move helping opponent:
**		the trickiest to catch, reduce the score on some
**		difficult conditions...
*/
static int		basic_rules(t_grid *game, t_threat_params *threat_p)
{
	int		threat;

	threat = (threat_p->token == PLAYER_TOKEN) ? -1 : 1;
	if (threat_p->level == THREAT_LOW)
		threat = 1;
	else if (threat_p->level == THREAT_HIGH)
	{
		threat = (threat_p->token == PLAYER_TOKEN) ? -2 : 40;
		if (game->player->difficulty >= 2)
			threat = (threat_p->token == PLAYER_TOKEN) ? 20 : 40;
	}
	else if (threat_p->level >= THREAT_VERY_HIGH)
	{
		threat = (threat_p->token == PLAYER_TOKEN) ? 10 : 500000;
		if (game->player->difficulty >= 2)
			threat = (threat_p->token == PLAYER_TOKEN) ? 100000 : 500000;
	}
	return (threat);
}

static int		boundary_rules(t_grid *game, t_threat_params *threat_p,
								t_vec2 pos, t_vec2 dir)
{
	int		threat;

	(void) game;
	(void) threat_p;
	(void) pos;
	(void) dir;
	threat = 0;
	return (threat);
}

static void		propagate_score(t_grid *game, t_threat_params *threat_p,
								t_vec2 pos, t_vec2 dir)
{
	char	p;
	int		x;
	int		y;
	int		threat;

	x = pos.x + dir.x;
	y = pos.y + dir.y;
	if (x >= game->col || x < 0 || y >= game->lin || y < 0)
		return ;
	p = game->grid[y][x];
	if (p == threat_p->token)
	{
		threat_p->level++;
		threat_p->score_map[y][x] = INT_MIN;
		propagate_score(game, threat_p, vector2(x, y), dir);
	}
	else
	{
		threat = basic_rules(game, threat_p);
		if (game->player->difficulty >= 2)
			threat += boundary_rules(game, threat_p, pos, dir);
		threat_p->score_map[y][x] += threat;
	}
}

static void		check_threat_levels(t_grid *game, int **score_map)
{
	t_threat_params		threat_p;
	char				p;
	int					i;
	int					j;

	threat_p.score_map = score_map;
	i = 0;
	while (i < game->lin)
	{
		j = 0;
		while (j < game->col)
		{
			p = game->grid[i][j];
			if (p == PLAYER_TOKEN || p == AI_TOKEN)
			{
				score_map[i][j] = INT_MIN;
				threat_p.token = p;
				threat_p.level = THREAT_LOW;
				propagate_score(game, &threat_p, vector2(j, i), vector2(-1, -1));
				threat_p.level = THREAT_LOW;
				propagate_score(game, &threat_p, vector2(j, i), vector2( 0, -1));
				threat_p.level = THREAT_LOW;
				propagate_score(game, &threat_p, vector2(j, i), vector2( 1, -1));
				threat_p.level = THREAT_LOW;
				propagate_score(game, &threat_p, vector2(j, i), vector2(-1, 0));
				threat_p.level = THREAT_LOW;
				propagate_score(game, &threat_p, vector2(j, i), vector2( 1, 0));
				threat_p.level = THREAT_LOW;
				propagate_score(game, &threat_p, vector2(j, i), vector2(-1, 1));
				threat_p.level = THREAT_LOW;
				propagate_score(game, &threat_p, vector2(j, i), vector2( 0, 1));
				threat_p.level = THREAT_LOW;
				propagate_score(game, &threat_p, vector2(j, i), vector2( 1, 1));
			}
			j++;
		}
		i++;
	}
}

static int	get_ground_score(t_grid *game, int **score_map, int col)
{
	int		score;
	int		i;

	i = -1;
	score = INT_MIN;
	while (++i < game->lin)
	{
		if (game->grid[i][col] == '.')
			score = score_map[i][col];
	}
	return (score);
}

static int	best_column(t_grid *game, int **score_map)
{
	int		score_max;
	int		score;
	int		col;
	int		i;
	int		j;

	i = 0;
	score_max = INT_MIN;
	while (i < game->lin)
	{
		j = 0;
		while (j < game->col)
		{
			score = get_ground_score(game, score_map, j);
			if (score > score_max)
			{
				score_max = score;
				col = j;
			}
			j++;
		}
		i++;
	}
	return (col);
}

int		ai_play_turn(t_grid *game)
{
	int		**score_map;
	int		play_index;

	score_map = new_score_map(game->col, game->lin);
	check_threat_levels(game, score_map);
	play_index = best_column(game, score_map);
	destroy_score_map(score_map, game->lin);
	return (play_index);
}
