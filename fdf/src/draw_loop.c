/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:16:46 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 19:08:48 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#ifdef DEBUG

static void	draw_gui(t_mlx_sess *p)
{
	draw_debug_gui(p);
}

#else

static void	draw_gui(t_mlx_sess *p)
{
	(void)p;
}

#endif

#ifdef BONUS

int			draw_loop(void *p)
{
	t_mlx_sess		*sess;
	struct timeval	tval_now;
	struct timeval	tval_tic;

	sess = (t_mlx_sess *)p;
	gettimeofday(&tval_now, NULL);
	timersub(&tval_now, &sess->last_tval, &tval_tic);
	if (tval_tic.tv_usec > FPS && sess->need_update)
	{
		gettimeofday(&sess->last_tval, NULL);
		clear_canvas(sess, sess->options.bg_color);
		draw_3dgrid(sess);
		mlx_put_image_to_window(sess->sess, sess->win, sess->img->img, 0, 0);
		draw_gui(sess);
		sess->need_update = 0;
	}
	return (0);
}

#else

int			draw_loop(void *p)
{
	(void)p;
	return (0);
}

#endif
