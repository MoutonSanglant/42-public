/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 17:29:05 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 22:17:35 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		set_perspective_camera(t_mlx_sess *sess)
{
	t_mat4x4	tmp;
	t_vec3f		loc;

	loc.x = 0;
	loc.y = sess->options.distance;
	loc.z = 0;
	sess->camera.near = .1f;
	identity_matrix4(sess->world);
	rotation_z_matrix4(&tmp, RAD(135));
	matrix4_product(&tmp, sess->world);
	rotation_x_matrix4(&tmp, RAD(-20));
	matrix4_product(&tmp, sess->world);
	translation_matrix4(&tmp, loc);
	matrix4_product(&tmp, sess->world);
	perspective_projection_matrix4(sess->projection, &sess->camera);
}

static void		set_orthographic_camera(t_mlx_sess *sess)
{
	t_mat4x4	tmp;
	t_vec3f		loc;

	loc.x = 0;
	loc.y = sess->options.distance * 6;
	loc.z = 0;
	sess->camera.top = .1f;
	sess->camera.bottom = -sess->camera.top;
	sess->camera.right = .1f * sess->camera.aspect;
	sess->camera.left = -sess->camera.right;
	sess->camera.near = 1.f;
	identity_matrix4(sess->world);
	rotation_z_matrix4(&tmp, RAD(135));
	matrix4_product(&tmp, sess->world);
	rotation_x_matrix4(&tmp, RAD(-20));
	matrix4_product(&tmp, sess->world);
	translation_matrix4(&tmp, loc);
	matrix4_product(&tmp, sess->world);
	orthographic_projection_matrix4(sess->projection, &sess->camera);
}

void			camera(t_mlx_sess *sess, char *str)
{
	if (ft_strequ(str, "perspective"))
		set_perspective_camera(sess);
	else if (ft_strequ(str, "orthographic"))
		set_orthographic_camera(sess);
	else
	{
		ft_putendl_fd("Error: incorrect camera format", 2);
		exit(155);
	}
}
