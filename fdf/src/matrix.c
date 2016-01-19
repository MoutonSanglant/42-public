/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 21:09:30 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/19 04:32:39 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix4	*identity_matrix4(t_matrix4 *m)
{
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
	return (m);
}

t_matrix4	*inverse_matrix4(t_matrix4 *m)
{
	return (m);
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
t_matrix4	*translate_matrix4(t_matrix4 *m, t_vector3 v)
{
	/*
	t_matrix4	A;
	t_matrix4	B;

	A[0][0] = (*m)[0][0];
	A[0][1] = (*m)[0][1];
	A[0][2] = (*m)[0][2];
	A[0][3] = (*m)[0][3];
	A[1][0] = (*m)[1][0];
	A[1][1] = (*m)[1][1];
	A[1][2] = (*m)[1][2];
	A[1][3] = (*m)[1][3];
	A[2][0] = (*m)[2][0];
	A[2][1] = (*m)[2][1];
	A[2][2] = (*m)[2][2];
	A[2][3] = (*m)[2][3];
	A[3][0] = (*m)[3][0];
	A[3][1] = (*m)[3][1];
	A[3][2] = (*m)[3][2];
	A[3][3] = (*m)[3][3];

	B[0][0] = 1;
	B[0][1] = 0;
	B[0][2] = 0;
	B[0][3] = 0;
	B[1][0] = 0;
	B[1][1] = 1;
	B[1][2] = 0;
	B[1][3] = 0;
	B[2][0] = 0;
	B[2][1] = 0;
	B[2][2] = 1;
	B[2][3] = 0;
	B[3][0] = v.x;
	B[3][1] = v.y;
	B[3][2] = v.z;
	B[3][3] = 1;
	*/

	(*m)[0][0] = 1;
	(*m)[0][1] = 0;
	(*m)[0][2] = 0;
	(*m)[0][3] += v.x;
	(*m)[1][0] = 0;
	(*m)[1][1] = 1;
	(*m)[1][2] = 0;
	(*m)[1][3] += v.y;
	(*m)[2][0] = 0;
	(*m)[2][1] = 0;
	(*m)[2][2] = 1;
	(*m)[2][3] += v.z;
	(*m)[3][0] += 0;
	(*m)[3][1] += 0;
	(*m)[3][2] += 0;
	(*m)[3][3] = 1;
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
	(*m)[3][0] += v.x;
	(*m)[3][1] += v.y;
	(*m)[3][2] += v.z;
	(*m)[3][3] = 1;
*/

	/*
	** left-multiply (pre-multiply)
	*/
	/*
	(*m)[0][0] = B[0][0] * A[0][0] + B[0][1] * A[1][0] + B[0][2] * A[2][0] + B[0][3] * A[3][0];
	(*m)[0][1] = B[0][0] * A[0][1] + B[0][1] * A[1][1] + B[0][2] * A[2][1] + B[0][3] * A[3][1];
	(*m)[0][2] = B[0][0] * A[0][2] + B[0][1] * A[1][2] + B[0][2] * A[2][2] + B[0][3] * A[3][2];
	(*m)[0][3] = B[0][0] * A[0][3] + B[0][1] * A[1][3] + B[0][2] * A[2][3] + B[0][3] * A[3][3];
	(*m)[1][0] = B[1][0] * A[0][0] + B[1][1] * A[1][0] + B[1][2] * A[2][0] + B[1][3] * A[3][0];
	(*m)[1][1] = B[1][0] * A[0][1] + B[1][1] * A[1][1] + B[1][2] * A[2][1] + B[1][3] * A[3][1];
	(*m)[1][2] = B[1][0] * A[0][2] + B[1][1] * A[1][2] + B[1][2] * A[2][2] + B[1][3] * A[3][2];
	(*m)[1][3] = B[1][0] * A[0][3] + B[1][1] * A[1][3] + B[1][2] * A[2][3] + B[1][3] * A[3][3];
	(*m)[2][0] = B[2][0] * A[0][0] + B[2][1] * A[1][0] + B[2][2] * A[2][0] + B[2][3] * A[3][0];
	(*m)[2][1] = B[2][0] * A[0][1] + B[2][1] * A[1][1] + B[2][2] * A[2][1] + B[2][3] * A[3][1];
	(*m)[2][2] = B[2][0] * A[0][2] + B[2][1] * A[1][2] + B[2][2] * A[2][2] + B[2][3] * A[3][2];
	(*m)[2][3] = B[2][0] * A[0][3] + B[2][1] * A[1][3] + B[2][2] * A[2][3] + B[2][3] * A[3][3];
	(*m)[3][0] = B[3][0] * A[0][0] + B[3][1] * A[1][0] + B[3][2] * A[2][0] + B[3][3] * A[3][0];
	(*m)[3][1] = B[3][0] * A[0][1] + B[3][1] * A[1][1] + B[3][2] * A[2][1] + B[3][3] * A[3][1];
	(*m)[3][2] = B[3][0] * A[0][2] + B[3][1] * A[1][2] + B[3][2] * A[2][2] + B[3][3] * A[3][2];
	(*m)[3][3] = B[3][0] * A[0][3] + B[3][1] * A[1][3] + B[3][2] * A[2][3] + B[3][3] * A[3][3];
	//*/

	/*
	** right-multiply (post-multiply)
	*/
	/*
	(*m)[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0] + A[0][3] * B[3][0];
	(*m)[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1] + A[0][2] * B[2][1] + A[0][3] * B[3][1];
	(*m)[0][2] = A[0][0] * B[0][2] + A[0][1] * B[1][2] + A[0][2] * B[2][2] + A[0][3] * B[3][2];
	(*m)[0][3] = A[0][0] * B[0][3] + A[0][1] * B[1][3] + A[0][2] * B[2][3] + A[0][3] * B[3][3];
	(*m)[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0] + A[1][2] * B[2][0] + A[1][3] * B[3][0];
	(*m)[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1] + A[1][2] * B[2][1] + A[1][3] * B[3][1];
	(*m)[1][2] = A[1][0] * B[0][2] + A[1][1] * B[1][2] + A[1][2] * B[2][2] + A[1][3] * B[3][2];
	(*m)[1][3] = A[1][0] * B[0][3] + A[1][1] * B[1][3] + A[1][2] * B[2][3] + A[1][3] * B[3][3];
	(*m)[2][0] = A[2][0] * B[0][0] + A[2][1] * B[1][0] + A[2][2] * B[2][0] + A[2][3] * B[3][0];
	(*m)[2][1] = A[2][0] * B[0][1] + A[2][1] * B[1][1] + A[2][2] * B[2][1] + A[2][3] * B[3][1];
	(*m)[2][2] = A[2][0] * B[0][2] + A[2][1] * B[1][2] + A[2][2] * B[2][2] + A[2][3] * B[3][2];
	(*m)[2][3] = A[2][0] * B[0][3] + A[2][1] * B[1][3] + A[2][2] * B[2][3] + A[2][3] * B[3][3];
	(*m)[3][0] = A[3][0] * B[0][0] + A[3][1] * B[1][0] + A[3][2] * B[2][0] + A[3][3] * B[3][0];
	(*m)[3][1] = A[3][0] * B[0][1] + A[3][1] * B[1][1] + A[3][2] * B[2][1] + A[3][3] * B[3][1];
	(*m)[3][2] = A[3][0] * B[0][2] + A[3][1] * B[1][2] + A[3][2] * B[2][2] + A[3][3] * B[3][2];
	(*m)[3][3] = A[3][0] * B[0][3] + A[3][1] * B[1][3] + A[3][2] * B[2][3] + A[3][3] * B[3][3];
	//*/

	/*
	//(*m)[0][0] = v.x;
	(*m)[3][0] += v.x;
	(*m)[3][1] += v.y;
	(*m)[3][2] += v.z;
	*/
	return (m);
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
t_matrix4	*scale_matrix4(t_matrix4 *m, t_vector3 v)
{
	(*m)[0][0] += v.x;
	(*m)[1][1] += v.y;
	(*m)[2][2] += v.z;
	return (m);
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
t_matrix4	*rotate_matrix4(t_matrix4 *m, double alpha)
{
	// Rotate on X
	//(*m)[0][0] = 1
	(void) m;
	(void) alpha;
	return (m);
}

/*
** orthographic projection: just remove the z component
** perspective projection: 
** 
**
** 1 0     0       0
** 0 1     0       0
** 0 0 (N + F)/N  -F
** 0 0    1/N      0
**
**
** N is Near viewing plane distance
** F is Far viewing plane distance
*/
t_matrix4	*projection_matrix4(t_matrix4 *A, t_matrix4 *B)
{
	(void) B;
	return (A);
}

/*
** dot product ?
*/