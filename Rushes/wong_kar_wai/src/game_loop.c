/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 17:46:15 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/31 23:16:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

static int	game_inputs(t_sess *sess, t_win **p_win, int c, t_task *loop_func)
{
	int		row;
	int		col;
	t_vec2	coord;
	t_vec2	row_col;

	refresh_window(*p_win);
	if ((sess->player_input = c) == c && c == KEY_DOWN)
		board_step(sess, p_win);
	else if ((sess->player_input = c) == c && c == KEY_UP)
		board_step(sess, p_win);
	else if ((sess->player_input = c) == c && c == KEY_RIGHT)
		board_step(sess, p_win);
	else if ((sess->player_input = c) == c && c == KEY_LEFT)
		board_step(sess, p_win);
	else if ((sess->player_input = c) == c && c == 96)
		board_step(sess, p_win);
	else if (c == 127)
	{
		getmaxyx(stdscr, row, col);
		row_col.y = MENU_HEIGHT(row);
		row_col.x = MENU_WIDTH(col);
		coord.y = MENU_Y(LINES, row);
		coord.x = MENU_X(COLS, col);
		swap_windows(p_win, row_col, coord, MENU_TITLE);
		loop_func->loop_f = &menu_loop;
	}
	return (0);
}

void		game_loop(t_sess *sess, t_win **p_win, t_task *loop_func)
{
	t_win	*win;

	win = *p_win;
	if (LINES != sess->row || COLS != sess->col)
	{
		getmaxyx(stdscr, sess->row, sess->col);
		if (sess->row < GAME_MIN_Y || sess->col < GAME_MIN_X)
		{
			endwin();
			ft_putendl(GAME_ERR_MSG);
			exit(1);
		}
		win->height = GAME_HEIGHT(sess->row);
		win->width = GAME_WIDTH(sess->col);
		win->y = GAME_Y(LINES, sess->row);
		win->x = GAME_X(COLS, sess->col);
		refresh_window(win);
	}
	putline(sess, win);
	putcol(sess, win);
	sess->input = wgetch(win->self);
	input_handler(sess, p_win, &game_inputs, loop_func);
}
