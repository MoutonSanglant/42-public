/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 17:45:42 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/31 23:16:00 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

static int	menu_inputs(t_sess *sess, t_win **p_win, int c, t_task *loop_func)
{
	t_win	*win;
	int		row;
	int		col;
	t_vec2	coord;
	t_vec2	row_col;

	(void)sess;
	win = *p_win;
	if (c < 48 || c > 50)
		mvwprintw(win->self, 6, (win->width - 13) / 2, "Wrong choice!");
	else if (c == 48)
	{
		endwin();
		exit(0);
	}
	else if (c == 49)
	{
		getmaxyx(stdscr, row, col);
		row_col.y = MENU_HEIGHT(row);
		row_col.x = MENU_WIDTH(col);
		coord.y = MENU_Y(LINES, row);
		coord.x = MENU_X(COLS, col);
		swap_windows(p_win, row_col, coord, GAME_TITLE);
		(*p_win)->caption = ft_strdup("Appuyez sur les fleches du clavier");
		(*p_win)->caption2 = ft_strdup("pour deplacer les pieces");
		refresh_window(*p_win);
		restart_game(sess);
		loop_func->loop_f = &game_loop;
	}
	else if (c == 50)
	{
		getmaxyx(stdscr, row, col);
		row_col.y = MENU_HEIGHT(row);
		row_col.x = MENU_WIDTH(col);
		coord.y = MENU_Y(LINES, row);
		coord.x = MENU_X(COLS, col);
		swap_windows(p_win, row_col, coord, OPTIONS_TITLE);
		loop_func->loop_f = &options_loop;
	}
	return (0);
}

void		menu_loop(t_sess *sess, t_win **p_win, t_task *loop_func)
{
	t_win	*win;
	int		size;

	win = *p_win;
	size = (win->width - ft_strlen("1. Start the game")) / 2;
	if (size < 3)
		size = 3;
	if (LINES != sess->row || COLS != sess->col)
	{
		getmaxyx(stdscr, sess->row, sess->col);
		if (sess->row < GAME_MIN_Y || sess->col < GAME_MIN_X)
		{
			endwin();
			ft_putendl(GAME_ERR_MSG);
			exit(1);
		}
		win->height = MENU_HEIGHT(sess->row);
		win->width = MENU_WIDTH(sess->col);
		win->y = MENU_Y(LINES, sess->row);
		win->x = MENU_X(COLS, sess->col);
		refresh_window(win);
	}
	mvwaddnstr(win->self, 1, size, "1. Start the game", win->width / 2);
	mvwaddnstr(win->self, 2, size, "2. Options", win->width / 2);
	mvwaddnstr(win->self, 4, size, "0. EXIT", win->width / 2);
	sess->input = wgetch(win->self);
	input_handler(sess, p_win, &menu_inputs, loop_func);
}
