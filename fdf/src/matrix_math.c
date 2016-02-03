/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 00:37:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/03 12:48:11 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	view_to_projection(t_vec3f v, t_mat4x4 *m)
{
	(void) v;
	(void) m;
}

void	world_to_view(t_vec3f v, t_mat4x4 *m)
{
	(void) v;
	(void) m;
}

/*
** Transpose a matrix to switch between column-vector
** matrices and row-vector matrices
*/
void		transpose_matrix4(t_mat4x4 *m)
{
	t_mat4x4	A;

	A[0] = (*m)[0];
	A[1] = (*m)[1];
	A[2] = (*m)[2];
	A[3] = (*m)[3];
	A[4] = (*m)[4];
	A[5] = (*m)[5];
	A[6] = (*m)[6];
	A[7] = (*m)[7];
	A[8] = (*m)[8];
	A[9] = (*m)[9];
	A[10] = (*m)[10];
	A[11] = (*m)[11];
	A[12] = (*m)[12];
	A[13] = (*m)[13];
	A[14] = (*m)[14];
	A[15] = (*m)[15];

	(*m)[0] = A[0];
	(*m)[1] = A[4];
	(*m)[2] = A[8];
	(*m)[3] = A[12];
	(*m)[4] = A[1];
	(*m)[5] = A[5];
	(*m)[6] = A[9];
	(*m)[7] = A[13];
	(*m)[8] = A[2];
	(*m)[9] = A[6];
	(*m)[10] = A[10];
	(*m)[11] = A[14];
	(*m)[12] = A[3];
	(*m)[13] = A[7];
	(*m)[14] = A[11];
	(*m)[15] = A[15];
}

void		matrix4_product(t_mat4x4 *b, t_mat4x4 *out)
{
	t_mat4x4	a;

	a[0] = (*out)[0];
	a[1] = (*out)[1];
	a[2] = (*out)[2];
	a[3] = (*out)[3];
	a[4] = (*out)[4];
	a[5] = (*out)[5];
	a[6] = (*out)[6];
	a[7] = (*out)[7];
	a[8] = (*out)[8];
	a[9] = (*out)[9];
	a[10] = (*out)[10];
	a[11] = (*out)[11];
	a[12] = (*out)[12];
	a[13] = (*out)[13];
	a[14] = (*out)[14];
	a[15] = (*out)[15];


	int i = 0;
	while (i < 4)
	{
		int j = 0;
		while (j < 4)
		{
			(*out)[j + i * 4] = (*b)[i * 4] * a[j]
							+ (*b)[1 + i * 4] * a[4 + j]
							+ (*b)[2 + i * 4] * a[8 + j]
							+ (*b)[3 + i * 4] * a[12 + j];
			j++;
		}
		i++;
	}

	return ;
	// ab
	i = 0;
	while (i < 4)
	{
		int j = 0;
		while (j < 4)
		{
			(*out)[j + i * 4] = a[i * 4] * (*b)[j]
							+ a[1 + i * 4] * (*b)[4 + j]
							+ a[2 + i * 4] * (*b)[8 + j]
							+ a[3 + i * 4] * (*b)[12 + j];
			j++;
		}
		i++;
	}
	//ba
	(*out)[0] = (*b)[0] * a[0] + (*b)[1] * a[4] + (*b)[2] * a[8] + (*b)[3] * a[12];
	(*out)[1] = (*b)[0] * a[1] + (*b)[1] * a[5] + (*b)[2] * a[9] + (*b)[3] * a[13];
	(*out)[2] = (*b)[0] * a[2] + (*b)[1] * a[6] + (*b)[2] * a[10] + (*b)[3] * a[14];
	(*out)[3] = (*b)[0] * a[3] + (*b)[1] * a[7] + (*b)[2] * a[11] + (*b)[3] * a[15];

	(*out)[4] = (*b)[4] * a[0] + (*b)[5] * a[4] + (*b)[6] * a[8] + (*b)[7] * a[12];
	(*out)[5] = (*b)[4] * a[1] + (*b)[5] * a[5] + (*b)[6] * a[9] + (*b)[7] * a[13];
	(*out)[6] = (*b)[4] * a[2] + (*b)[5] * a[6] + (*b)[6] * a[10] + (*b)[7] * a[14];
	(*out)[7] = (*b)[4] * a[3] + (*b)[5] * a[7] + (*b)[6] * a[11] + (*b)[7] * a[15];

	(*out)[8] = (*b)[8] * a[0] + (*b)[9] * a[4] + (*b)[10] * a[8] + (*b)[11] * a[12];
	(*out)[9] = (*b)[8] * a[1] + (*b)[9] * a[5] + (*b)[10] * a[9] + (*b)[11] * a[13];
	(*out)[10] = (*b)[8] * a[2] + (*b)[9] * a[6] + (*b)[10] * a[10] + (*b)[11] * a[14];
	(*out)[11] = (*b)[8] * a[3] + (*b)[9] * a[7] + (*b)[10] * a[11] + (*b)[11] * a[15];

	(*out)[12] = (*b)[12] * a[0] + (*b)[13] * a[4] + (*b)[14] * a[8] + (*b)[15] * a[12];
	(*out)[13] = (*b)[12] * a[1] + (*b)[13] * a[5] + (*b)[14] * a[9] + (*b)[15] * a[13];
	(*out)[14] = (*b)[12] * a[2] + (*b)[13] * a[6] + (*b)[14] * a[10] + (*b)[15] * a[14];
	(*out)[15] = (*b)[12] * a[3] + (*b)[13] * a[7] + (*b)[14] * a[11] + (*b)[15] * a[15];
	//*/
}

/*
** Xaxis.x Yaxis.x Zaxis.x Trans.x
** Xaxis.y Yaxis.y Zaxis.y Trans.y
** Xaxis.z Yaxis.z Zaxis.z Trans.z
**    0       0       0       1
*/
t_vec3f	apply_matrix4(t_vec3f a, t_mat4x4 *m)
{
	t_vec3f b;

	b.x = a.x;
	b.y = a.y;
	b.z = a.z;

	/*
	a.x = (*m)[0] * b.x + (*m)[4] * b.y + (*m)[8] * b.z + (*m)[12];
	a.y = (*m)[1] * b.x + (*m)[5] * b.y + (*m)[9] * b.z + (*m)[13];
	a.z = (*m)[2] * b.x + (*m)[6] * b.y + (*m)[10] * b.z + (*m)[14];
	w = (*m)[3] * b.x + (*m)[7] * b.y + (*m)[11] * b.z + (*m)[15];
	/*/
	// affine transformation matrix operation
	a.x = (*m)[0] * b.x + (*m)[1] * b.y + (*m)[2] * b.z + (*m)[3];
	a.y = (*m)[4] * b.x + (*m)[5] * b.y + (*m)[6] * b.z + (*m)[7];
	a.z = (*m)[8] * b.x + (*m)[9] * b.y + (*m)[10] * b.z + (*m)[11];
	//*/
	// projection matrix operation
	float w;
	w = (*m)[12] * b.x + (*m)[13] * b.y + (*m)[14] * b.z + (*m)[15];
	//w = (*m)[3] * b.x + (*m)[7] * b.y + (*m)[11] * b.z + (*m)[15];
	if (w != 1)
	{
		a.x = a.x / w;
		a.y = a.y / w;
		a.z = a.z / w;
	}
	//*/
	return(a);
}

/*
** No need to implement Model to World since
** there will be only one model displayed
*/
