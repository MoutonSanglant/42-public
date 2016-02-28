/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puissance4.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 14:00:28 by gdruel            #+#    #+#             */
/*   Updated: 2016/02/27 18:38:20 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUISSANCE4_H
# define PUISSANCE4_H

# include <time.h>
# include <stdlib.h>
# include <limits.h>

# include "libft.h"

# define PLAYER_TOKEN 'X'
# define AI_TOKEN 'O'

typedef struct	s_vec2
{
	int		x;
	int		y;
}				t_vec2;

typedef struct	s_player
{
	struct s_player		*other;
	char				*name;
	char				*color;
	char				token;
	int					difficulty;
}				t_player;

/*
**	state: à 0 tant que la partie est en cours, passe à 1 quand
**	un joueur gagne ou si la grille est pleine
*/

typedef struct	s_grid
{
	t_player	players[2];
	t_player	*player;
	int			state;
	int			lin;
	int			col;
	char		**grid;
}				t_grid;

typedef enum	e_threat_level
{
	THREAT_ZERO = 0x0,
	THREAT_LOW = 0x1,
	THREAT_HIGH = 0x2,
	THREAT_VERY_HIGH = 0x3
}				t_threat_level;

typedef struct	s_threat_params
{
	int				**score_map;
	char			token;
	t_threat_level	level;
}				t_threat_params;

t_vec2			vector2(int x, int y);
t_grid			*init(t_grid *game, int lines, int columns);
void			destroy_game(t_grid *game, int lines);
void			display_grid(t_grid *game);
void			place(int col, t_grid *game, int id);
void			check_victory(t_grid *game);

int				human_play_turn(t_grid *game);
int				ai_play_turn(t_grid *grid);
int				**new_score_map(int width, int height);
void			destroy_score_map(int **score_map, int height);

#endif
