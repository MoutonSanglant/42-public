/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 11:55:58 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/31 22:57:45 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

t_win	*create_window(t_vec2 coord, int starty, int startx, char *title)
{
	t_win *win;

	win = (t_win *)malloc(sizeof(t_win));
	win->self = newwin(coord.y, coord.x, starty, startx);
	win->width = coord.x;
	win->height = coord.y;
	win->x = startx;
	win->y = starty;
	win->title = ft_strdup(title);
	win->caption = NULL;
	refresh_window(win);
	return (win);
}
