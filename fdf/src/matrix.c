/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 21:09:30 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/20 03:21:27 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	identity_matrix4(t_matrix4 *m)
{
/*
	(*m)[0][0] = 1;
	(*m)[0][1] = 0;
	(*m)[0][2] = 0;
	(*m)[0][3] = 0;
	(*m)[1][0] = 0;
	(*m)[1][1] = 1;
	(*m)[1][2] = 0;
	(*m)[1][3] = 0;
	(*m)[2][0] = 0;
	(*m)[2][1] = 0;
	(*m)[2][2] = 1;
	(*m)[2][3] = 0;
	(*m)[3][0] = 0;
	(*m)[3][1] = 0;
	(*m)[3][2] = 0;
	(*m)[3][3] = 1;
*/
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

void	inverse_matrix4(t_matrix4 *m, t_matrix4 *invOut)
{
	double inv[16];
	double	det;
	int i;

	inv[0] = (*m)[5]  * (*m)[10] * (*m)[15]
		- (*m)[5]  * (*m)[11] * (*m)[14]
		- (*m)[9]  * (*m)[6]  * (*m)[15]
		+ (*m)[9]  * (*m)[7]  * (*m)[14]
		+ (*m)[13] * (*m)[6]  * (*m)[11]
		- (*m)[13] * (*m)[7]  * (*m)[10];

	inv[4] = -(*m)[4]  * (*m)[10] * (*m)[15]
		+ (*m)[4]  * (*m)[11] * (*m)[14]
		+ (*m)[8]  * (*m)[6]  * (*m)[15]
		- (*m)[8]  * (*m)[7]  * (*m)[14]
		- (*m)[12] * (*m)[6]  * (*m)[11]
		+ (*m)[12] * (*m)[7]  * (*m)[10];

	inv[8] = (*m)[4]  * (*m)[9] * (*m)[15]
		- (*m)[4]  * (*m)[11] * (*m)[13]
		- (*m)[8]  * (*m)[5] * (*m)[15]
		+ (*m)[8]  * (*m)[7] * (*m)[13]
		+ (*m)[12] * (*m)[5] * (*m)[11]
		- (*m)[12] * (*m)[7] * (*m)[9];

	inv[12] = -(*m)[4]  * (*m)[9] * (*m)[14]
		+ (*m)[4]  * (*m)[10] * (*m)[13]
		+ (*m)[8]  * (*m)[5] * (*m)[14]
		- (*m)[8]  * (*m)[6] * (*m)[13]
		- (*m)[12] * (*m)[5] * (*m)[10]
		+ (*m)[12] * (*m)[6] * (*m)[9];

	inv[1] = -(*m)[1]  * (*m)[10] * (*m)[15]
		+ (*m)[1]  * (*m)[11] * (*m)[14]
		+ (*m)[9]  * (*m)[2] * (*m)[15]
		- (*m)[9]  * (*m)[3] * (*m)[14]
		- (*m)[13] * (*m)[2] * (*m)[11]
		+ (*m)[13] * (*m)[3] * (*m)[10];

	inv[5] = (*m)[0]  * (*m)[10] * (*m)[15]
		- (*m)[0]  * (*m)[11] * (*m)[14]
		- (*m)[8]  * (*m)[2] * (*m)[15]
		+ (*m)[8]  * (*m)[3] * (*m)[14]
		+ (*m)[12] * (*m)[2] * (*m)[11]
		- (*m)[12] * (*m)[3] * (*m)[10];

	inv[9] = -(*m)[0]  * (*m)[9] * (*m)[15]
		+ (*m)[0]  * (*m)[11] * (*m)[13]
		+ (*m)[8]  * (*m)[1] * (*m)[15]
		- (*m)[8]  * (*m)[3] * (*m)[13]
		- (*m)[12] * (*m)[1] * (*m)[11]
		+ (*m)[12] * (*m)[3] * (*m)[9];

	inv[13] = (*m)[0]  * (*m)[9] * (*m)[14]
		- (*m)[0]  * (*m)[10] * (*m)[13]
		- (*m)[8]  * (*m)[1] * (*m)[14]
		+ (*m)[8]  * (*m)[2] * (*m)[13]
		+ (*m)[12] * (*m)[1] * (*m)[10]
		- (*m)[12] * (*m)[2] * (*m)[9];

	inv[2] = (*m)[1]  * (*m)[6] * (*m)[15]
		- (*m)[1]  * (*m)[7] * (*m)[14]
		- (*m)[5]  * (*m)[2] * (*m)[15]
		+ (*m)[5]  * (*m)[3] * (*m)[14]
		+ (*m)[13] * (*m)[2] * (*m)[7]
		- (*m)[13] * (*m)[3] * (*m)[6];

	inv[6] = -(*m)[0]  * (*m)[6] * (*m)[15]
		+ (*m)[0]  * (*m)[7] * (*m)[14]
		+ (*m)[4]  * (*m)[2] * (*m)[15]
		- (*m)[4]  * (*m)[3] * (*m)[14]
		- (*m)[12] * (*m)[2] * (*m)[7]
		+ (*m)[12] * (*m)[3] * (*m)[6];

	inv[10] = (*m)[0]  * (*m)[5] * (*m)[15]
		- (*m)[0]  * (*m)[7] * (*m)[13]
		- (*m)[4]  * (*m)[1] * (*m)[15]
		+ (*m)[4]  * (*m)[3] * (*m)[13]
		+ (*m)[12] * (*m)[1] * (*m)[7]
		- (*m)[12] * (*m)[3] * (*m)[5];

	inv[14] = -(*m)[0]  * (*m)[5] * (*m)[14]
		+ (*m)[0]  * (*m)[6] * (*m)[13]
		+ (*m)[4]  * (*m)[1] * (*m)[14]
		- (*m)[4]  * (*m)[2] * (*m)[13]
		- (*m)[12] * (*m)[1] * (*m)[6]
		+ (*m)[12] * (*m)[2] * (*m)[5];

	inv[3] = -(*m)[1] * (*m)[6] * (*m)[11]
		+ (*m)[1] * (*m)[7] * (*m)[10]
		+ (*m)[5] * (*m)[2] * (*m)[11]
		- (*m)[5] * (*m)[3] * (*m)[10]
		- (*m)[9] * (*m)[2] * (*m)[7]
		+ (*m)[9] * (*m)[3] * (*m)[6];

	inv[7] = (*m)[0] * (*m)[6] * (*m)[11]
		- (*m)[0] * (*m)[7] * (*m)[10]
		- (*m)[4] * (*m)[2] * (*m)[11]
		+ (*m)[4] * (*m)[3] * (*m)[10]
		+ (*m)[8] * (*m)[2] * (*m)[7]
		- (*m)[8] * (*m)[3] * (*m)[6];

	inv[11] = -(*m)[0] * (*m)[5] * (*m)[11]
		+ (*m)[0] * (*m)[7] * (*m)[9]
		+ (*m)[4] * (*m)[1] * (*m)[11]
		- (*m)[4] * (*m)[3] * (*m)[9]
		- (*m)[8] * (*m)[1] * (*m)[7]
		+ (*m)[8] * (*m)[3] * (*m)[5];

	inv[15] = (*m)[0] * (*m)[5] * (*m)[10]
		- (*m)[0] * (*m)[6] * (*m)[9]
		- (*m)[4] * (*m)[1] * (*m)[10]
		+ (*m)[4] * (*m)[2] * (*m)[9]
		+ (*m)[8] * (*m)[1] * (*m)[6]
		- (*m)[8] * (*m)[2] * (*m)[5];

	det = (*m)[0] * inv[0] + (*m)[1] * inv[4] + (*m)[2] * inv[8] + (*m)[3] * inv[12];

	//if (det == 0)
	//	return NULL;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
		(*invOut)[i] = inv[i] * det;
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
//t_matrix4	*translate_matrix4(t_matrix4 *A[4][4], t_matrix4 *B[4][4])
void	translation_matrix4(t_matrix4 *m, t_vector3 v)
{
	identity_matrix4(m);
	/*
	(*m)[12] = v.x;
	(*m)[13] = v.y;
	(*m)[14] = v.z;
	*/
	(*m)[3] = v.x;
	(*m)[7] = v.y;
	(*m)[11] = v.z;
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
//t_matrix4	*scale_matrix4(t_matrix4 *A[4][4], t_matrix4 *B[4][4])
void	scaling_matrix4(t_matrix4 *m, t_vector3 v)
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
//t_matrix4	*rotate_matrix4(t_matrix4 *A, t_matrix4 *B)
void	rotationX_matrix4(t_matrix4 *m, double alpha)
{
	identity_matrix4(m);
	/*
	(*m)[5] = cos(alpha);
	(*m)[6] = -sin(alpha);
	(*m)[9] = sin(alpha);
	(*m)[10] = cos(alpha);
	*/
	(*m)[5] = cos(alpha);
	(*m)[6] = sin(alpha);
	(*m)[9] = -sin(alpha);
	(*m)[10] = cos(alpha);
}

void	rotationY_matrix4(t_matrix4 *m, double alpha)
{
	identity_matrix4(m);
	/*
	(*m)[0] = cos(alpha);
	(*m)[2] = sin(alpha);
	(*m)[8] = -sin(alpha);
	(*m)[10] = cos(alpha);
	*/
	(*m)[0] = cos(alpha);
	(*m)[2] = -sin(alpha);
	(*m)[8] = sin(alpha);
	(*m)[10] = cos(alpha);
}

void	rotationZ_matrix4(t_matrix4 *m, double alpha)
{
	identity_matrix4(m);
	/*
	(*m)[0] = cos(alpha);
	(*m)[1] = -sin(alpha);
	(*m)[4] = sin(alpha);
	(*m)[5] = cos(alpha);
	*/
	(*m)[0] = cos(alpha);
	(*m)[1] = sin(alpha);
	(*m)[4] = -sin(alpha);
	(*m)[5] = cos(alpha);
}

/*
** orthographic projection: just remove the z component
**
** N is Near viewing plane distance
** F is Far viewing plane distance
*/
void	perspective_projection_matrix4(t_matrix4 *m, t_vector2 FOV,
										int far, int near)
{
	(void) FOV;
	identity_matrix4(m);
	/*
	** WIKI
	(*m)[10] = (far + near) / near;
	(*m)[14] = -far;
	(*m)[11] = 1/near;
	*/
	(*m)[0] = atan(RAD((FOV.x / 2)));
	(*m)[5] = atan(RAD((FOV.y / 2)));
	(*m)[10] = -((far + near) / (far - near));
	(*m)[11] = -((2 * (near * far)) / (far - near));
	(*m)[14] = -1;
	//(*m)[11] = -1;
	//(*m)[14] = -((2 * (near * far)) / (far - near));

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
void	orthographic_projection_matrix4(t_matrix4 *m, t_vector2 size,
										int far, int near)
{
	identity_matrix4(m);
	(*m)[0] = 1 / size.x;
	(*m)[5] = 1 / size.y;
	(*m)[10] = -(2 / (far - near));
	(*m)[11] = -((far + near) / (far - near));
	(*m)[15] = 1;

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
