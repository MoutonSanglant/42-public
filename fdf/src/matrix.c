/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 21:09:30 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/02 13:37:36 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	Matrices in row-major columns
*/

void	identity_matrix4(t_mat4x4 *m)
{
	(*m)[0] = 1.f;
	(*m)[1] = 0.f;
	(*m)[2] = 0.f;
	(*m)[3] = 0.f;
	(*m)[4] = 0.f;
	(*m)[5] = 1.f;
	(*m)[6] = 0.f;
	(*m)[7] = 0.f;
	(*m)[8] = 0.f;
	(*m)[9] = 0.f;
	(*m)[10] = 1.f;
	(*m)[11] = 0.f;
	(*m)[12] = 0.f;
	(*m)[13] = 0.f;
	(*m)[14] = 0.f;
	(*m)[15] = 1.f;

}


/*
** translation: movement of a point from its origin
** to another location in 3-space by a constant offset
**
** 1 0 0 X
** 0 1 0 Y
** 0 0 1 Z
** 0 0 0 1
*/
//t_mat4x4	*translate_matrix4(t_mat4x4 *A[4][4], t_mat4x4 *B[4][4])
void	translation_matrix4(t_mat4x4 *m, t_vec3f v)
{
	identity_matrix4(m);
	/*
	(*m)[12] = v.x;
	(*m)[13] = v.y;
	(*m)[14] = v.z;
	/*/
	(*m)[3] = v.x;
	(*m)[7] = v.y;
	(*m)[11] = v.z;
	//*/
}

/*
** scaling: multiplying the position of a vertex by a
** scalar value. Scale the vertex in respect of the origin
**
** X 0 0 0
** 0 Y 0 0
** 0 0 Z 0
** 0 0 0 1
*/
//t_mat4x4	*scale_matrix4(t_mat4x4 *A[4][4], t_mat4x4 *B[4][4])
void	scaling_matrix4(t_mat4x4 *m, t_vec3f v)
{
	identity_matrix4(m);
	(*m)[0] = v.x;
	(*m)[5] = v.y;
	(*m)[10] = v.z;
}

/*
** rotation: depend on the axis around which a point
** is to be rotated
**
** X-axis
**
** 1  0     0   0
** 0 cos@ -sin@ 0
** 0 sin@  cos@ 0
** 0  0     0   1
**
** Y-axis
**
**  cos@ 0 sin@ 0
**   0   1  0   0
** -sin@ 0 cos@ 0
**   0   0  0   1
**
** Z-axis
**
** cos@ -sin@ 0 0
** sin@ cos@  0 0
**  0    0    1 0
**  0    0    0 1
**
**
** @ is the angle of the rotation
*/
//t_mat4x4	*rotate_matrix4(t_mat4x4 *A, t_mat4x4 *B)
void	rotationX_matrix4(t_mat4x4 *m, float alpha)
{
	identity_matrix4(m);
	(*m)[5] = cosf(alpha);
	(*m)[6] = sinf(alpha);
	(*m)[9] = -sinf(alpha);
	(*m)[10] = cosf(alpha);
}

void	rotationY_matrix4(t_mat4x4 *m, float alpha)
{
	identity_matrix4(m);
	(*m)[0] = cosf(alpha);
	(*m)[2] = -sinf(alpha);
	(*m)[8] = sinf(alpha);
	(*m)[10] = cosf(alpha);
}

void	rotationZ_matrix4(t_mat4x4 *m, float alpha)
{
	identity_matrix4(m);
	(*m)[0] = cosf(alpha);
	(*m)[1] = sinf(alpha);
	(*m)[4] = -sinf(alpha);
	(*m)[5] = cosf(alpha);
}

/*
** perspective projection:
**
** 1 0     0       0
** 0 1     0       0
** 0 0 (N + F)/N  -F
** 0 0    1/N      0
**
** N is Near viewing plane distance
** F is Far viewing plane distance
*/
void	perspective_projection_matrix4(t_mat4x4 *m, float angleOfView,
										float aspect, int far, int near)
{
	float scale;
	scale = 1.f / tanf(angleOfView * .5f * M_PI / 180.f);

	(void)aspect;
	identity_matrix4(m);
	(*m)[0] = scale / aspect;
	(*m)[5] = scale;
	//(*m)[10] = -(far / (far - near));
	(*m)[10] = (near + far) / (near - far);
	(*m)[11] = -1.f;
	//(*m)[14] = -((far * near) / (far - near));
	(*m)[14] = 2.f * far * near / (near - far);
	(*m)[15] = 0.f;
	// transpose m in column-major order
	transpose_matrix4(m);
}

/*
** orthographic projection: just remove the z component
**
** N is Near viewing plane distance
** F is Far viewing plane distance
*/
void	orthographic_projection_matrix4(t_mat4x4 *m, float t, float b, float l,											float r, int far, int near)
{
	identity_matrix4(m);
	(*m)[0] = 2.f / (r - l);
	(*m)[3] = -((r + l) / (r - l));
	(*m)[5] = 2.f / (t - b);
	(*m)[7] = -((t + b) / (t - b));
	(*m)[10] = -(2.f / (far - near));
	(*m)[11] = -((far + near) / (far - near));
	(*m)[15] = 1.f;
	transpose_matrix4(m);

	/*
	(*m)[0] = 1 / size.x;
	(*m)[5] = 1 / size.y;
	(*m)[10] = -(2 / (far - near));
	(*m)[11] = -((far + near) / (far - near));
	(*m)[15] = 1;
	*/
}

void	view_frustum_matrix4()
{
// http://duriansoftware.com/joe/An-intro-to-modern-OpenGL.-Chapter-3:-3D-transformation-and-projection.html
/*
	return mat4(
			vec4(1.0/tan(angle_of_view),           0.0, 0.0, 0.0),
			vec4(0.0, aspect_ratio/tan(angle_of_view),  0.0, 0.0),
			vec4(0.0, 0.0,    (z_far+z_near)/(z_far-z_near), 1.0),
			vec4(0.0, 0.0, -2.0*z_far*z_near/(z_far-z_near), 0.0)
			);
*/
}
