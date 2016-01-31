/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 10:34:02 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/31 22:54:50 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

static void	init_win(void)
{
	initscr();
	cbreak();
	raw();
	noecho();
	curs_set(0);
	start_color();
}

static void	init_colors(void)
{
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(4, COLOR_CYAN, COLOR_BLUE);
	init_pair(8, COLOR_RED, COLOR_GREEN);
	init_pair(16, COLOR_BLUE, COLOR_YELLOW);
	init_pair(32, COLOR_CYAN, COLOR_MAGENTA);
	init_pair(64, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(128, COLOR_WHITE, COLOR_BLUE);
	init_pair(256, COLOR_RED, COLOR_YELLOW);
	init_pair(512, COLOR_BLACK, COLOR_GREEN);
	init_pair(1024, COLOR_YELLOW, COLOR_RED);
	init_pair(2048, COLOR_BLACK, COLOR_WHITE);
}

int			main(int argc, char **argv)
{
	t_sess	sess;
	t_task	loop;
	t_win	*win;
	t_vec2	coord;

	if (argc < 1 || argv[0][0] == '\0')
		return (1);
	if (getenv("ESCDELAY") == NULL)
		ESCDELAY = 25;
	init_win();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, sess.row, sess.col);
	coord.y = MENU_HEIGHT(sess.row);
	coord.x = MENU_WIDTH(sess.col);
	win = create_window(coord, MENU_Y(LINES, sess.row),
							MENU_X(COLS, sess.col), "Menu");
	win->blank_line = NULL;
	init_colors();
	loop.loop_f = &menu_loop;
	sess.board_width = 4;
	while (1)
		loop.loop_f(&sess, &win, &loop);
	endwin();
	return (0);
}
