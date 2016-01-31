/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 17:29:05 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/03 12:52:33 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_perspective_camera(t_mlx_sess *sess)
{
	t_mat4x4	tmp;
	t_vec3f		loc;

	loc.x = 18;
	loc.y = 20;
	loc.z = -6;
	identity_matrix4(sess->world);
	rotation_z_matrix4(&tmp, RAD(180));
	matrix4_product(&tmp, sess->world);
	translation_matrix4(&tmp, loc);
	matrix4_product(&tmp, sess->world);
	rotation_x_matrix4(&tmp, RAD(-10));
	matrix4_product(&tmp, sess->world);
	rotation_z_matrix4(&tmp, RAD(-25));
	matrix4_product(&tmp, sess->world);
	perspective_projection_matrix4(sess->projection, &sess->camera);
}

void	set_orthographic_camera(t_mlx_sess *sess)
{
	t_mat4x4	tmp;
	t_vec3f		loc;

	loc.x = 0;
	loc.y = 135;
	loc.z = 0;
	identity_matrix4(sess->world);
	rotation_z_matrix4(&tmp, RAD(135));
	matrix4_product(&tmp, sess->world);
	rotation_x_matrix4(&tmp, RAD(-20));
	matrix4_product(&tmp, sess->world);
	translation_matrix4(&tmp, loc);
	matrix4_product(&tmp, sess->world);
	sess->camera.right = .1f * sess->camera.aspect;
	sess->camera.top = .1f;
	sess->camera.left = -sess->camera.right;
	sess->camera.bottom = -sess->camera.top;
	sess->camera.near = 1.f;
	orthographic_projection_matrix4(sess->projection, &sess->camera);
}
