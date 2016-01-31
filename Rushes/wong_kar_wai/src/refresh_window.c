/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 19:00:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/31 23:18:33 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	refresh_window(t_win *win)
{
	if (win->caption)
	{
		mvprintw(GAME_Y(LINES, 0) + GAME_HEIGHT(LINES), COLS / 2
				- ft_strlen(win->caption) / 2, win->caption);
		mvprintw(GAME_Y(LINES, 0) + GAME_HEIGHT(LINES) + 1, COLS / 2
				- ft_strlen(win->caption2) / 2, win->caption2);
	}
	refresh();
	clear();
	wborder(win->self, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(win->self);
	delwin(win->self);
	win->self = newwin(win->height, win->width, win->y, win->x);
	box(win->self, 0, 0);
	wrefresh(win->self);
	keypad(win->self, TRUE);
	if (win->blank_line)
		ft_strdel(&win->blank_line);
	win->blank_line = ft_strnew(win->width / 4);
	win->blank_line = (char *)ft_memset((void *)win->blank_line, ' ',
							win->width / 4 - 1);
	wattrset(win->self, A_STANDOUT | A_BOLD | COLOR_PAIR(1));
	mvwprintw(win->self, 0, (win->width - ft_strlen(win->title)) / 2,
							win->title);
	wattroff(win->self, A_STANDOUT | A_BOLD | COLOR_PAIR(1));
}
