/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dgrid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:52:02 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/19 04:49:08 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_joints(t_mlx_sess *p, t_vector3 v, t_vector3 v2)
{
	t_vector2	from;
	t_vector2	to;
	t_vector4	vertex;
	//t_vector3	vertex;

	vertex.x = v.x;
	vertex.y = v.y;
	vertex.z = v.z;
	vertex.w = 1;
	//vertex = apply_matrix4(vertex, p->view);
	vertex = apply_matrix4(vertex, p->view);
	from.x = vertex.x;
	from.y = vertex.y;

	vertex.x = v2.x;
	vertex.y = v2.y;
	vertex.z = v2.z;
	vertex.w = 1;
	vertex = apply_matrix4(vertex, p->view);
	to.x = vertex.x;
	to.y = vertex.y;

	draw_line((t_mlx_sess *)p, &from, &to);
}

void	draw_3dgrid(t_mlx_sess *p)
{
//	static t_vector3	from;
//	static t_vector3	to;

	int		x;
	int		y;

	x = 0;
	y = 0;

	clear_canvas(p, 0x000000);

	while (x < 9)
	{
		while (y < 9)
		{
			draw_joints(p, p->grid[x + y * 10], p->grid[x + y * 10 + 1]);
			draw_joints(p, p->grid[x + y * 10], p->grid[x + y * 10 + 10]);
			y++;
		}
		y = 0;
		x++;
	}
}
