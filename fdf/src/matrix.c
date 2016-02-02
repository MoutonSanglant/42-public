/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 21:09:30 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/02 18:51:36 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	Translation: movement of a point from its origin
**	to another location in 3-space by a constant offset
**		1 0 0 X
**		0 1 0 Y
**		0 0 1 Z
**		0 0 0 1
*/

void	translation_matrix4(t_mat4x4 *m, t_vec3f v)
{
	identity_matrix4(m);
	(*m)[3] = v.x;
	(*m)[7] = v.y;
	(*m)[11] = v.z;
}

/*
**	Scaling: multiplying the position of a vertex by a
**	scalar value. Scale the vertex in respect of the origin
**		X 0 0 0
**		0 Y 0 0
**		0 0 Z 0
**		0 0 0 1
*/

void	scaling_matrix4(t_mat4x4 *m, t_vec3f v)
{
	identity_matrix4(m);
	(*m)[0] = v.x;
	(*m)[5] = v.y;
	(*m)[10] = v.z;
}

/*
**	Rotation: depend on the axis around which a point
**	is to be rotated
**	==============
**	X-axis
**	1  0     0   0
**	0 cos@ -sin@ 0
**	0 sin@  cos@ 0
**	0  0     0   1
**	==============
**	@ is the angle of the rotation
*/

void	rotation_x_matrix4(t_mat4x4 *m, float alpha)
{
	identity_matrix4(m);
	(*m)[5] = cosf(alpha);
	(*m)[6] = sinf(alpha);
	(*m)[9] = -sinf(alpha);
	(*m)[10] = cosf(alpha);
}

/*
**	Y-axis
**	==============
**	cos@ 0 sin@ 0
**	 0   1  0   0
**	-sin@ 0 cos@ 0
**	 0   0  0   1
**	==============
** @ is the angle of the rotation
*/

void	rotation_y_matrix4(t_mat4x4 *m, float alpha)
{
	identity_matrix4(m);
	(*m)[0] = cosf(alpha);
	(*m)[2] = -sinf(alpha);
	(*m)[8] = sinf(alpha);
	(*m)[10] = cosf(alpha);
}

/*
**	Z-axis
**	==============
**	cos@ -sin@ 0 0
**	sin@ cos@  0 0
**	 0    0    1 0
**	 0    0    0 1
**	==============
**	@ is the angle of the rotation
*/

void	rotation_z_matrix4(t_mat4x4 *m, float alpha)
{
	identity_matrix4(m);
	(*m)[0] = cosf(alpha);
	(*m)[1] = sinf(alpha);
	(*m)[4] = -sinf(alpha);
	(*m)[5] = cosf(alpha);
}
