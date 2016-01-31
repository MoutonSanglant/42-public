/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putcol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 22:38:07 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/31 22:42:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void		putcol(t_sess *sess, t_win *win)
{
	int w;
	int h;

	(void)sess;
	w = 1;
	h = 1;
	while (h < win->height - 1)
	{
		while (w < 4)
			mvwprintw(win->self, h, w++ * (win->width / 4), "|");
		w = 1;
		h++;
	}
}
