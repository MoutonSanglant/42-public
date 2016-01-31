/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 15:28:06 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/31 23:11:20 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	destroy_window(t_win *win)
{
	wborder(win->self, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(win->self);
	delwin(win->self);
	ft_memdel((void **)&win);
}
