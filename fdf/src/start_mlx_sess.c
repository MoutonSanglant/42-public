/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx_sess.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:40:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 15:29:17 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#ifdef LINUX

static void set_mlx_hooks(t_mlx_sess *sess)
{
	mlx_hook(sess->win, KeyPress, KeyPressMask, &keydown, (void *)sess);
	mlx_key_hook(sess->win, &keypress, (void *)sess);
	mlx_expose_hook(sess->win, &expose, (void *)sess);
	mlx_loop_hook(sess->sess, &draw_loop, (void *)sess);
}

#else

static void set_mlx_hooks(t_mlx_sess *sess)
{
	mlx_hook(sess->win, KEYPRESS, KEYPRESSMASK, &keydown, (void *)sess);
	mlx_key_hook(sess->win, &keypress, (void *)sess);
	mlx_expose_hook(sess->win, &expose, (void *)sess);
	mlx_loop_hook(sess->sess, &draw_loop, (void *)sess);
}

#endif

void	start_mlx_sess(t_mlx_sess *sess)
{
	set_mlx_hooks(sess);
	mlx_loop(sess->sess);
}
