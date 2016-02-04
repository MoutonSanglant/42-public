/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:03:16 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 16:17:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_around_center(t_mlx_sess *sess, char c, int dir)
{
	t_mat4x4	m_iworld;
	t_mat4x4	m_rot;

	inverse_matrix4(sess->world, &m_iworld);
	identity_matrix4(&m_rot);
	if (c == 'z')
		rotation_z_matrix4(&m_rot, RAD(3 * dir));
	else if (c == 'y')
		rotation_y_matrix4(&m_rot, RAD(3 * dir));
	else if (c == 'x')
		rotation_x_matrix4(&m_rot, RAD(3 * dir));
	matrix4_product(&m_rot, &m_iworld);
	inverse_matrix4(&m_iworld, sess->world);
}

static void	translation_events(t_mlx_sess *sess, int key)
{
	t_mat4x4	m_loc;
	t_vec3f		loc;

	loc.x = 0;
	loc.y = 0;
	loc.z = 0;
	identity_matrix4(&m_loc);
	if (key == KEY_NUMPAD_MORE)
		loc.y = -1;
	else if (key == KEY_NUMPAD_LESS)
		loc.y = 1;
	else if (key == KEY_LEFT)
		loc.x = -1;
	else if (key == KEY_RIGHT)
		loc.x = 1;
	else if (key == KEY_UP)
		loc.z = -1;
	else if (key == KEY_DOWN)
		loc.z = 1;
	else if (key == KEY_PAGE_UP)
		change_grid_z(sess->grid, 1.1f);
	else if (key == KEY_PAGE_DOWN)
		change_grid_z(sess->grid, 0.9f);
	translation_matrix4(&m_loc, loc);
	matrix4_product(&m_loc, sess->world);
}

/*
**	ft_putchar('\n');
**	ft_putnbr(key);
*/

int			keydown(int key, void *p)
{
	t_mlx_sess	*sess;

	sess = (t_mlx_sess *)p;
	sess->need_update = 1;
	if (key == KEY_B)
		sess->bresenham = (sess->bresenham) ? 0 : 1;
	else if (key == KEY_O)
	{
		param->faces_color = param->lines_color;
		param->lines_color = param->bg_color;
	}
	else if (key == KEY_O)
		set_orthographic_camera(sess);
	else if (key == KEY_P)
		set_perspective_camera(sess);
	else if (key == KEY_Q)
		rotate_around_center(sess, 'y', 1);
	else if (key == KEY_E)
		rotate_around_center(sess, 'y', -1);
	else if (key == KEY_A)
		rotate_around_center(sess, 'z', -1);
	else if (key == KEY_D)
		rotate_around_center(sess, 'z', 1);
	else if (key == KEY_W)
		rotate_around_center(sess, 'x', -1);
	else if (key == KEY_S)
		rotate_around_center(sess, 'x', 1);
	else
		translation_events(sess, key);
	return (0);
}
