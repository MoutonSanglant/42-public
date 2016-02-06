/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:16:46 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/06 03:31:17 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#ifdef DEBUG

static void	draw_gui(t_mlx_sess *p)
{
	draw_debug_gui(p);
}

#else

static void	draw_help_tooltip(void *s, void *w, int line)
{
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[+] Zoom in");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[-] Zoom out");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[Arrows] Pan");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
					"[W/A/S/D/Q/E] Rotate");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
					"[PAGE UP/DOWN] Rise/Lower vertices");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[O]rthographic");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[P]erspective");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
					"[B]ackface culling");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
					"[I]nvert colors");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[Z]-Buffer");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[F]ill faces");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
					"[*] Line weight");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
					"[0-9] Color schemes");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[ESC] Exit");
}

static void	draw_gui(t_mlx_sess *p)
{
	void	*s;
	void	*w;
	int		line;

	if (!p->options.tooltip)
		return ;
	line = 1;
	s = p->sess;
	w = p->win;
	if (p->img->filename)
	{
		mlx_string_put(s, w, 5, line * GUI_LINE_HEIGHT, WHITE, "Source file: ");
		mlx_string_put(s, w, 155, line++ * GUI_LINE_HEIGHT, WHITE,
														p->img->filename);
	}
	mlx_string_put(s, w, 5, line++ * GUI_LINE_HEIGHT, 0x00ffffff, "[H]elp");
	draw_help_tooltip(s, w, line);
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

/*
**	TODO
**	Do something ?
*/

int			draw_loop(void *p)
{
	(void)p;
	return (0);
}

#endif
