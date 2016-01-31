/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_random_tile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 23:21:55 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/31 23:23:10 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"
static void		set_tile(size_t *board, size_t board_size,
								size_t written_tile, size_t rand_nb)
{
	size_t	i;
	i = 0;
	while (i < board_size)
	{
		if (board[i] == 0 && written_tile == 0)
		{
			board[i] = rand_nb;
			return ;
		}
		else if (board[i] == 0)
			written_tile--;
		i++;
	}
}

int		fill_random_tile(t_sess *sess, int salt)
	{
		int		rand_nb;
		size_t	empty_tiles;
		size_t	i;

		srand(salt);
		rand_nb = rand() % 100;
		if (rand_nb < 13)
			rand_nb = 4;
		else
			rand_nb = 2;
		i = 0;
		empty_tiles = 0;
		while (i < sess->board_size)
		{
			if (sess->board[i] == 0)
				empty_tiles++;
			i++;
		}
		set_tile(sess->board, sess->board_size, rand() % empty_tiles, rand_nb);
		if (empty_tiles == 1)
			return (0);
		return (1);
	}
