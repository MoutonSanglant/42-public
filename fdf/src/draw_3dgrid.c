/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dgrid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:52:02 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/21 01:47:00 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

static int		rasterize_coord(t_mlx_sess *p, t_vector3 in, t_vector2 *out)
{
	// Coords are in screen coodinate
	// 1 - Pass to NDC coordinates
	// 2 - Pass to raster coordinates
(void) p;

	// This is a point in Camera space
	out->x = in.x / -in.z;
	out->y = in.y / -in.z;

	if (ceil(ABS(out->x)) > p->canvasW * .5f || ceil(ABS(out->y)) > p->canvasH * .5f)
		return (1);

	// convert point coordinates to raster coordinates

	// normalize x & y (set in [0,1] range)
	out->x = (out->x + p->canvasW * .5f) / p->canvasW;
	out->y = (out->y + p->canvasH * .5f) / p->canvasH;
	// Coords are now in NDC space

	// Pass to rang [0,x] & [0,y]
	out->x = floor(out->x * p->width);
	out->y = floor((1 - out->y) * p->width); // invert y

	return (0);
}

static int draw_point(t_mlx_sess *p, t_vector3 vertex, t_vector2 *point, t_matrix4 *mvp)
{
	vertex = apply_matrix4(vertex, mvp);
	vertex = apply_matrix4(vertex, p->worldToCamera);
	//vertex = apply_matrix4(vertex, p->projection);
	//point = rasterize_coord(p, vertex);
	if (rasterize_coord(p, vertex, point))
		return (0);

	//ft_putstr("z (view): ");
	//ft_putnbr((*mvp)[11]);
	//ft_putchar('\n');
	//ft_putendl("==============");
	if ((int)point->x < 0 || (int)point->x >= p->width || (int)point->y < 0 || (int)point->y >= p->height)
		return (0);

	draw_line((t_mlx_sess *)p, point, point);

	return (1);
}

//static void	draw_joints(t_mlx_sess *p, t_vector3 v, t_vector3 v2, t_matrix4 *p->world, t_matrix4 *W2C)
static void		draw_triangle(t_mlx_sess *p, t_triangle *triangle, t_matrix4 *mvp)
{
	t_vector3	a;
	t_vector3	b;
	t_vector3	c;
	//t_vector3	vertices[3];
	t_vector2	pixels[3];

	a = triangle->a;
	b = triangle->b;
	c = triangle->c;
	if (draw_point(p, a, &pixels[0], mvp) && draw_point(p, b, &pixels[1], mvp) && draw_point(p, c, &pixels[2], mvp))
	{
		p->col = 0x00ffffff;
		draw_line((t_mlx_sess *)p, &pixels[0], &pixels[1]);
		draw_line((t_mlx_sess *)p, &pixels[1], &pixels[2]);
		draw_line((t_mlx_sess *)p, &pixels[2], &pixels[0]);
	}

	/*
	vertices[0] = apply_matrix4(a, mvp);
	vertices[0] = apply_matrix4(a, p->worldToCamera);
	//vertex = apply_matrix4(a, p->projection);
	if (rasterize_coord(p, vertices[0], &pixels[0]))
		return ;
	vertices[1] = apply_matrix4(b, mvp);
	vertices[1] = apply_matrix4(b, p->worldToCamera);
	if (rasterize_coord(p, vertices[1], &pixels[1]))
		return ;
	vertices[2] = apply_matrix4(c, mvp);
	vertices[2] = apply_matrix4(c, p->worldToCamera);
	if (rasterize_coord(p, vertices[2], &pixels[2]))
		return ;
*/
	/*
	if ((int)from.x <= 0 || (int)from.x >= p->width || (int)from.y <= 0 || (int)from.y >= p->height)
		return ;
	if ((int)to.x <= 0 || (int)to.x >= p->width || (int)to.y <= 0 || (int)to.y >= p->height)
		return ;
	*/
}

void	draw_3dgrid(t_mlx_sess *p)
{
//	static t_vector3	from;
//	static t_vector3	to;

	t_matrix4	mvp;
	t_matrix4	model;
	static t_matrix4	*trans = NULL;
	static int r = 0;
	t_matrix4	rot;
	t_matrix4	tmp;
	t_vector3 s;
	t_vector3 o;
	//t_vector3 ox;
	//t_vector3 oy;
	//t_vector3 oz;

	identity_matrix4(&model);
	// Scale
	//matrix4_product(&model, &tmp);
	s.x = 50.f;
	s.y = 50.f;
	s.z = 50.f;
	scaling_matrix4(&tmp, s);
	matrix4_product(&model, &tmp);

	// Rotate
	// Translate
	o.x = 0.f;
	o.y = 0.f;
	o.z = -1.f;
	translation_matrix4(&tmp, o);
	matrix4_product(&model, &tmp);

	// Transformation matrix = world * view * projection;
	// model
	identity_matrix4(&mvp);
	matrix4_product(&mvp, &model);
	// world
	// * view
	//matrix4_product(&model, p->view);
	// * projection
	matrix4_product(&mvp, p->world);
	//matrix4_product(&mvp, p->view);
	//matrix4_product(&mvp, p->projection);

	/*
	// draw gizmo
	o.x = 0.f;
	o.y = 0.f;
	o.z = 0.f;
	ox.x = 1.f;
	ox.y = 0.f;
	ox.z = 0.f;
	p->col = 0x00ff0000;
	//draw_joints(p, o, ox, p->world, &model);
	//draw_joints(p, o, ox, &mvp);
	oy.x = 0.f;
	oy.y = 1.f;
	oy.z = 0.f;
	p->col = 0x0000ff00;
	//draw_joints(p, o, oy, p->world, &model);
	//draw_joints(p, o, oy, &mvp);
	oz.x = 0.f;
	oz.y = 0.f;
	oz.z = -1.f;
	p->col = 0x0000ffff;
	//draw_joints(p, o, oz, p->world, &model);
	//draw_joints(p, o, oz, &mvp);
	*/
	p->col = 0x00ffffff;
	if (!trans)
	{
		trans = (t_matrix4 *)malloc(sizeof(t_matrix4));
		identity_matrix4(trans);
	}
	identity_matrix4(&model);
	// Scale
	s.x = 100.f;
	s.y = 100.f;
	s.z = 100.f;
	scaling_matrix4(&tmp, s);
	matrix4_product(&model, &tmp);

	// Rotate
	// Translate
	o.x = 17.f;
	o.y = 0.f;
	o.z = -1.f;
	translation_matrix4(&tmp, o);
	matrix4_product(&model, &tmp);

	o.x = -1000.f;
	o.y = -1000.f;
	o.z = 10.f;
	translation_matrix4(&tmp, o);
	//matrix4_product(trans, &tmp);

	// Rotate
	rotationZ_matrix4(&rot, RAD(r));
	//matrix4_product(&model, &rot);
	r += 5;

	// Model Matrix: Local
	identity_matrix4(&mvp);
	matrix4_product(&mvp, &model);
	//ft_putstr("z (local): ");
	//ft_putnbr(mvp[11]);
	//ft_putendl(" (should be -1)");
	// World (local-to-world)
	matrix4_product(&mvp, p->world);
	//ft_putstr("z (world): ");
	//ft_putnbr(mvp[11]);
	//ft_putendl(" (should be -1)");
	// Camera (world-to-camera)
	// we need the inverse of View
	//t_matrix4 iview;

	//inverse_matrix4(p->view, &iview);
	//matrix4_product(&mvp, &iview);
	//ft_putstr("z (view): ");
	//ft_putnbr(mvp[11]);
	//ft_putchar('\n');


	// Transformation matrix = world * view * projection;
	// model
	//matrix4_product(&model, p->projection);
	// world
	// * view
	//matrix4_product(&model, p->view);
	// * projection
	//matrix4_product(&mvp, p->projection);
	p->col = 0x00ff0000;

	//draw_triangle(p, &p->grid->triangles[100], &mvp);

	int		i;
	int		x = 0;
	int		y = 0;

	while (x < 12)
		draw_triangle(p, &p->cube[x++], &mvp);

	i = 0;
	x = 0;
	p->col = 0x00ffffff;
	//matrix4_product(&mvp, &model);
	while (x < p->grid->width)
	{
		while (y < p->grid->height)
		{
			draw_triangle(p, &p->grid->triangles[i++], &mvp);
			draw_triangle(p, &p->grid->triangles[i++], &mvp);
			//draw_joints(p, p->grid[x + y * 10], p->grid[x + y * 10 + 10], &mvp);
			//draw_joints(p, p->grid[x + y * 10], p->grid[x + y * 10 + 1], p->world, &model);
			//draw_joints(p, p->grid[x + y * 10], p->grid[x + y * 10 + 10], p->world, &model);
			y++;
		}
		y = 0;
		x++;
	}
}
