/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 18:05:49 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/02 18:15:47 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Perspective projection:
**
** 1 0     0       0
** 0 1     0       0
** 0 0 (N + F)/N  -F
** 0 0    1/N      0
**
** N is Near viewing plane distance
** F is Far viewing plane distance
*/

void	perspective_projection_matrix4(t_mat4x4 *m, t_camera *camera)
{
	float	scale;
	float	near;
	float	far;

	near = camera->near;
	far = camera->far;
	scale = 1.f / tanf(camera->angle_of_view * .5f * M_PI / 180.f);
	identity_matrix4(m);
	(*m)[0] = scale / camera->aspect;
	(*m)[5] = scale;
	(*m)[10] = (near + far) / (near - far);
	(*m)[11] = -1.f;
	(*m)[14] = 2.f * far * near / (near - far);
	(*m)[15] = 0.f;
	transpose_matrix4(m);
}

/*
** Orthographic projection:
**
** N is Near viewing plane distance
** F is Far viewing plane distance
*/

void	orthographic_projection_matrix4(t_mat4x4 *m, t_camera *camera)
{
	float	t;
	float	b;
	float	l;
	float	r;

	t = camera->top;
	b = camera->bottom;
	l = camera->left;
	r = camera->right;
	identity_matrix4(m);
	(*m)[0] = 2.f / (r - l);
	(*m)[3] = -((r + l) / (r - l));
	(*m)[5] = 2.f / (t - b);
	(*m)[7] = -((t + b) / (t - b));
	(*m)[10] = -(2.f / (camera->far - camera->near));
	(*m)[11] = -((camera->far + camera->near) / (camera->far - camera->near));
	(*m)[15] = 1.f;
	transpose_matrix4(m);
}
