/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 19:35:21 by framel            #+#    #+#             */
/*   Updated: 2016/01/31 22:50:28 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

static int		test_h_hh(int h, int *hh)
{
	if (h == 0 && *hh == 0)
	{
		*hh = *hh + 1;
		return (1);
	}
	return (0);
}

static void		draw_bg(t_sess *sess, t_win *win, int h, int w)
{
	char	*str;
	int		hh;
	int		idx;

	idx = h + (w / 2) * sess->board_width;
	if (sess->board[idx] != 0)
	{
		wattron(win->self, COLOR_PAIR(sess->board[idx]));
		hh = 0;
		while (hh < win->height / 4)
		{
			if (test_h_hh(h, &hh))
				continue ;
			mvwprintw(win->self, hh + h * (win->height / 4),
					w * (win->width / 4) / 2
					- ft_strlen(win->blank_line + 1) / 2, win->blank_line);
			hh++;
		}
		str = ft_itoa(sess->board[idx]);
		mvwprintw(win->self, h * (win->height / 4) + (win->height / 4) / 2,
				w * (win->width / 4) / 2 - ft_strlen(str) / 2, str);
		wattroff(win->self, COLOR_PAIR(sess->board[idx]));
		ft_strdel(&str);
	}
}

void			putline(t_sess *sess, t_win *win)
{
	int		w;
	int		h;

	w = 1;
	h = 0;
	while (w < (win->width - 1))
	{
		while (h < 4)
		{
			if (w % 2)
			{
				draw_bg(sess, win, h, w);
			}
			if (h > 0)
				mvwprintw(win->self, h * (win->height / 4), w, "-");
			h++;
		}
		h = 0;
		w++;
	}
}
