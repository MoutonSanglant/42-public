/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx_sess.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:40:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/09 12:16:46 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		close_button(int e, void *p)
{
	(void)e;
	(void)p;
	exit(0);
	return (0);
}

#ifdef BONUS

static void		set_mlx_hooks(t_mlx_sess *sess)
{
	mlx_hook(sess->win, 17, 0, &close_button, (void *)sess);
	mlx_hook(sess->win, KEYPRESS, KEYPRESSMASK, &keydown, (void *)sess);
	mlx_key_hook(sess->win, &keypress, (void *)sess);
	mlx_expose_hook(sess->win, &expose, (void *)sess);
	mlx_loop_hook(sess->sess, &draw_loop, (void *)sess);
}

#else

static void		set_mlx_hooks(t_mlx_sess *sess)
{
	mlx_key_hook(sess->win, &keypress, (void *)sess);
	mlx_expose_hook(sess->win, &expose, (void *)sess);
	mlx_loop_hook(sess->sess, &draw_loop, (void *)sess);
}

#endif

void			start_mlx_sess(t_mlx_sess *sess)
{
	camera(sess, "orthographic");
	set_mlx_hooks(sess);
	mlx_loop(sess->sess);
}
