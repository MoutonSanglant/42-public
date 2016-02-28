/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 01:20:47 by gdruel            #+#    #+#             */
/*   Updated: 2016/02/28 14:37:01 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puissance4.h"

static int		game_loop(t_grid *game, int (*play_fn[2])(t_grid *),
							int coin, int placed[2])
{
	if (++placed[coin] >= 22)
		return (!(game->state = 2));
	ft_putstr(game->player->color);
	ft_putstr(game->player->name);
	ft_putstr("\x1B[0m");
	ft_putendl(" turn. ");
	place(play_fn[coin](game), game, coin);
	return (!game->state);
}

static int		play(t_grid *game, int (*play_fn[2])(t_grid *))
{
	int		coin;
	int		placed[2];

	placed[0] = 0;
	placed[1] = 0;
	srand(time(0));
	coin = rand() % 2;
	game->player = &game->players[coin];
	while (game_loop(game, play_fn, coin, placed))
	{
		coin = (coin == 0) ? 1 : 0;
		game->player = &game->players[coin];
	}
	if (game->state == 1)
	{
		ft_putstr(game->player->color);
		ft_putstr(game->player->name);
		ft_putstr("\x1B[0m");
		ft_putendl(" wins !");
	}
	else
		ft_putendl("Nobody wins...");
	return (0);
}

static void		start_game(t_grid *game)
{
	int		(*play_functions[2])(t_grid *);
	char	*players;

	ft_putendl("How many players ? (1 - 2)");
	get_next_line(0, &players);
	play_functions[0] = human_play_turn;
	display_grid(game);
	if (ft_atoi(players) == 1)
	{
		game->players[0].name = ft_strdup("Player");
		game->players[1].name = ft_strjoin("AI ", ft_itoa(game->players[1].difficulty));
		play_functions[1] = ai_play_turn;
		play(game, play_functions);
	}
	else if (ft_atoi(players) == 2)
	{
		game->players[0].name = ft_strdup("Player 1");
		game->players[1].name = ft_strdup("Player 2");
		play_functions[1] = human_play_turn;
		play(game, play_functions);
	}
	else
		ft_putendl("Wrong number of players. Y U SO STUPID. Aborting.");
}

static int		clamp(int n, int min, int max)
{
	if (n > max)
		n = max;
	else if (n < min)
		n = min;
	return (n);
}

int				main(int argc, char const *argv[])
{
	t_grid	*game;

	if (!(argc == 3 || argc == 4) || ft_atoi(argv[1]) < 6 || ft_atoi(argv[2]) < 7)
	{
		ft_putendl("Error, noob");
		return (1);
	}
	else
	{
		if (!(game = ft_memalloc(sizeof(*game))))
			return (0);
		game = init(game, ft_atoi(argv[1]), ft_atoi(argv[2]));
		game->players[0].color = ft_strdup("\x1B[31m");
		game->players[1].color = ft_strdup("\x1B[32m");
		game->players[0].token = PLAYER_TOKEN;
		game->players[1].token = AI_TOKEN;
		game->players[0].other = &game->players[1];
		game->players[1].other = &game->players[0];
		game->players[0].difficulty = 0;
		game->players[1].difficulty = (argc == 4) ? clamp(ft_atoi(argv[3]), 1, 4) : 4;
		start_game(game);
	}
	destroy_game(game, game->lin);
	return (0);
}
