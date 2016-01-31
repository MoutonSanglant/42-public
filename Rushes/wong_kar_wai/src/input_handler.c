/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 11:08:59 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/31 23:13:57 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	input_handler(t_sess *sess, t_win **p_win,
						int (*callback)(t_sess *, t_win **, int, t_task *),
						t_task *loop_func)
{
	if (sess->input == 27)
	{
		endwin();
		exit(0);
	}
	callback(sess, p_win, sess->input, loop_func);
}
