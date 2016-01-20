/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dgrid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:52:02 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/20 03:14:30 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_joints(t_mlx_sess *p, t_vector3 v, t_vector3 v2, t_matrix4 *mvp)
{
	t_vector2	from;
	t_vector2	to;
	t_vector4	vertex;
	(void) to;
	(void) from;
	(void) p;
	(void) mvp;

	vertex.x = v.x;
	vertex.y = v.y;
	vertex.z = v.z;
	vertex.w = 1.f;
	apply_matrix4(vertex, mvp);
	/*if (vertex.w > 0)
	{
		if (vertex.x > 0)
			vertex.x /= vertex.w;
		if (vertex.y > 0)
			vertex.y /= vertex.y;
		if (vertex.z > 0)
			vertex.z /= vertex.z;
	}*/
	//vertex.w /= vertex.w;
	from.x = vertex.x;
	from.y = vertex.y;

	vertex.x = v2.x;
	vertex.y = v2.y;
	vertex.z = v2.z;
	vertex.w = 1.f;
	vertex = apply_matrix4(vertex, mvp);
	/*if (vertex.w > 0)
	{
		if (vertex.x > 0)
			vertex.x /= vertex.w;
		if (vertex.y > 0)
			vertex.y /= vertex.y;
		if (vertex.z > 0)
			vertex.z /= vertex.z;
	}*/
	//vertex.w /= vertex.w;
	to.x = vertex.x;
	to.y = vertex.y;
	//ft_putnbr(from.y);

	if (from.x < 0 || from.x >= 1000 || from.y < 0 || from.y >= 1000)
		return ;
	if (to.x < 0 || to.x >= 1000 || to.y < 0 || to.y >= 1000)
		return ;
	draw_line((t_mlx_sess *)p, &from, &to);
}

void	draw_3dgrid(t_mlx_sess *p)
{
//	static t_vector3	from;
//	static t_vector3	to;

	int		x = 0;
	int		y = 0;
	t_matrix4	mvp;
	t_matrix4	model;

	identity_matrix4(&mvp);
	multiply_matrix4(&mvp, p->view);
	multiply_matrix4(&mvp, p->projection);

	// draw gizmo
	t_vector3 o;
	t_vector3 ox;
	t_vector3 oy;
	t_vector3 oz;
	o.x = 0.f;
	o.y = 0.f;
	o.z = 0.f;
	ox.x = 100.f;
	ox.y = 0.f;
	ox.z = 0.f;
	p->col = 0x00ff0000;
	draw_joints(p, o, ox, &mvp);
	oy.x = 0.f;
	oy.y = 100.f;
	oy.z = 0.f;
	p->col = 0x0000ff00;
	draw_joints(p, o, oy, &mvp);
	oz.x = 0.f;
	oz.y = 0.f;
	oz.z = 100.f;
	p->col = 0x0000ffff;
	(void) oz;
	draw_joints(p, o, oz, &mvp);
	p->col = 0x00ffffff;

	identity_matrix4(&model);
	identity_matrix4(&mvp);
	o.x = 100.f;
	translation_matrix4(&model, o);
	//rotationY_matrix4(&model, RAD(30));
	multiply_matrix4(&mvp, &model);
	multiply_matrix4(&mvp, p->view);
	multiply_matrix4(&mvp, p->projection);

	while (x < 9)
	{
		while (y < 9)
		{
			draw_joints(p, p->grid[x + y * 10], p->grid[x + y * 10 + 1], &mvp);
			draw_joints(p, p->grid[x + y * 10], p->grid[x + y * 10 + 10], &mvp);
			y++;
		}
		y = 0;
		x++;
	}
}
