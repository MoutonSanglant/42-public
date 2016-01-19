/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 00:37:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/19 04:28:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	view_to_projection(t_vector3 v, t_matrix4 *m)
{
	(void) v;
	(void) m;
}

void	world_to_view(t_vector3 v, t_matrix4 *m)
{
	(void) v;
	(void) m;
}

t_vector4	apply_matrix4(t_vector4 v, t_matrix4 *m)
//t_vector3	apply_matrix4(t_vector3 v, t_matrix4 *m)
{
	t_matrix4	A;

	A[0][0] = (*m)[0][0] * v.x;
	A[0][1] = (*m)[0][1] * v.y;
	A[0][2] = (*m)[0][2] * v.z;
	A[0][3] = (*m)[0][3] * v.w;
	A[1][0] = (*m)[1][0] * v.x;
	A[1][1] = (*m)[1][1] * v.y;
	A[1][2] = (*m)[1][2] * v.z;
	A[1][3] = (*m)[1][3] * v.w;
	A[2][0] = (*m)[2][0] * v.x;
	A[2][1] = (*m)[2][1] * v.y;
	A[2][2] = (*m)[2][2] * v.z;
	A[2][3] = (*m)[2][3] * v.w;
	A[3][0] = (*m)[3][0] * v.x;
	A[3][1] = (*m)[3][1] * v.y;
	A[3][2] = (*m)[3][2] * v.z;
	A[3][3] = (*m)[3][3] * v.w;

	/*
	A[0][3] = (*m)[0][3];
	A[1][3] = (*m)[1][3];
	A[2][3] = (*m)[2][3];
	A[3][3] = (*m)[3][3];
	*/

	//v.x = A[0][0] + A[0][1] + A[0][2];
	//v.y = A[1][0] + A[1][1] + A[1][2];
	//v.z = A[2][0] + A[2][1] + A[2][2];
	v.x = A[0][0] + A[0][1] + A[0][2] + A[0][3];
	v.y = A[1][0] + A[1][1] + A[1][2] + A[1][3];
	v.z = A[2][0] + A[2][1] + A[2][2] + A[2][3];
	v.w = A[3][0] + A[3][1] + A[3][2] + A[3][3];

	return(v);
}

/*
** No need to implement Model to World since
** there will be only one model displayed
*/
