/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 00:37:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/03 20:31:48 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			copy_matrix4(t_mat4x4 *dst, const t_mat4x4 *src)
{
	int			i;

	i = -1;
	while (++i < 16)
		(*dst)[i] = (*src)[i];
}

/*
** Transpose a matrix to switch between column-vector
** matrices and row-vector matrices
*/

void			transpose_matrix4(t_mat4x4 *m)
{
	t_mat4x4	a;

	copy_matrix4(&a, m);
	(*m)[0] = a[0];
	(*m)[1] = a[4];
	(*m)[2] = a[8];
	(*m)[3] = a[12];
	(*m)[4] = a[1];
	(*m)[5] = a[5];
	(*m)[6] = a[9];
	(*m)[7] = a[13];
	(*m)[8] = a[2];
	(*m)[9] = a[6];
	(*m)[10] = a[10];
	(*m)[11] = a[14];
	(*m)[12] = a[3];
	(*m)[13] = a[7];
	(*m)[14] = a[11];
	(*m)[15] = a[15];
}

/*
**	while (i < 4)
**	{
**		j = 0;
**		while (j < 4)
**		{
**			(*out)[j + i * 4] = (*b)[i * 4] * a[j]
**							+ (*b)[1 + i * 4] * a[4 + j]
**							+ (*b)[2 + i * 4] * a[8 + j]
**							+ (*b)[3 + i * 4] * a[12 + j];
**			j++;
**		}
**		i++;
**	}
**	==========
**	BA product
*/

void			matrix4_product(t_mat4x4 *in, t_mat4x4 *out)
{
	t_mat4x4	a;
	t_mat4x4	b;

	copy_matrix4(&a, out);
	copy_matrix4(&b, in);
	(*out)[0] = b[0] * a[0] + b[1] * a[4] + b[2] * a[8] + b[3] * a[12];
	(*out)[1] = b[0] * a[1] + b[1] * a[5] + b[2] * a[9] + b[3] * a[13];
	(*out)[2] = b[0] * a[2] + b[1] * a[6] + b[2] * a[10] + b[3] * a[14];
	(*out)[3] = b[0] * a[3] + b[1] * a[7] + b[2] * a[11] + b[3] * a[15];
	(*out)[4] = b[4] * a[0] + b[5] * a[4] + b[6] * a[8] + b[7] * a[12];
	(*out)[5] = b[4] * a[1] + b[5] * a[5] + b[6] * a[9] + b[7] * a[13];
	(*out)[6] = b[4] * a[2] + b[5] * a[6] + b[6] * a[10] + b[7] * a[14];
	(*out)[7] = b[4] * a[3] + b[5] * a[7] + b[6] * a[11] + b[7] * a[15];
	(*out)[8] = b[8] * a[0] + b[9] * a[4] + b[10] * a[8] + b[11] * a[12];
	(*out)[9] = b[8] * a[1] + b[9] * a[5] + b[10] * a[9] + b[11] * a[13];
	(*out)[10] = b[8] * a[2] + b[9] * a[6] + b[10] * a[10] + b[11] * a[14];
	(*out)[11] = b[8] * a[3] + b[9] * a[7] + b[10] * a[11] + b[11] * a[15];
	(*out)[12] = b[12] * a[0] + b[13] * a[4] + b[14] * a[8] + b[15] * a[12];
	(*out)[13] = b[12] * a[1] + b[13] * a[5] + b[14] * a[9] + b[15] * a[13];
	(*out)[14] = b[12] * a[2] + b[13] * a[6] + b[14] * a[10] + b[15] * a[14];
	(*out)[15] = b[12] * a[3] + b[13] * a[7] + b[14] * a[11] + b[15] * a[15];
}

/*
**	Xaxis.x Yaxis.x Zaxis.x Trans.x
**	Xaxis.y Yaxis.y Zaxis.y Trans.y
**	Xaxis.z Yaxis.z Zaxis.z Trans.z
**		0       0       0       1
**	===============================
**	When 'w' is 1
**		-> affine transformation matrix operation
**	When 'w' is !1
**		-> projection matrix operation
*/

t_vec3f			apply_matrix4(t_vec3f a, t_mat4x4 *m)
{
	t_vec3f		b;
	float		w;

	b.x = a.x;
	b.y = a.y;
	b.z = a.z;
	a.x = (*m)[0] * b.x + (*m)[1] * b.y + (*m)[2] * b.z + (*m)[3];
	a.y = (*m)[4] * b.x + (*m)[5] * b.y + (*m)[6] * b.z + (*m)[7];
	a.z = (*m)[8] * b.x + (*m)[9] * b.y + (*m)[10] * b.z + (*m)[11];
	w = (*m)[12] * b.x + (*m)[13] * b.y + (*m)[14] * b.z + (*m)[15];
	if (w != 1)
	{
		a.x = a.x / w;
		a.y = a.y / w;
		a.z = a.z / w;
	}
	return (a);
}
