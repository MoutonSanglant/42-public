/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 23:19:23 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/31 23:21:12 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void			restart_game(t_sess *sess)
{
	sess->board_size = sess->board_width * sess->board_width;
	sess->board = (size_t *)malloc(sizeof(size_t) * sess->board_size);
	ft_memset(sess->board, 0, sizeof(size_t) * sess->board_size);

	fill_random_tile(sess, time(NULL));
	fill_random_tile(sess, 293238);
}
