/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dgrid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:52:02 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/29 04:52:26 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

static int		rasterize_coord(t_mlx_sess *p, t_vec3f in, t_vec3f *out)
{
	// IMPORTANT NOTE
	// I don't handle the FIT / OVERSCAN solutions to scale
	// the image in x or y.
	// This is on purpose, I don't want to provide a multiple
	// solution since it is a simple project, yet I should
	// choose one from these 2 solutions someday
	//
	// Yet, my goal now is to achieve to implement the
	// "projection matrix", certainly calling it inside this function

	t_vec3f NDCout;

	// Coords are in screen coodinate
	// 1 - Pass to NDC coordinates
	// 2 - Pass to raster coordinates

	// This is a point in Camera space
	out->x = in.x / -in.z * p->near; // we need to multiply x by near
	out->y = in.y / -in.z * p->near; // we need to multiply y by near

	// 1 - Convert points to NDC space
	// NDC space should be in range [-1, 1] (GPU convention)
	//NDCout.x = 2 * out->x / (r - l) - (r + l) / (r - l); !! NEXT LESSON !!
	//NDCout.y = 2 * out->y / (t - b) - (t + b) / (t - b); !! NEXT LESSON !!
	NDCout.x = (out->x + p->canvasR) / (2 * p->canvasR);
	NDCout.y = (out->y + p->canvasT) / (2 * p->canvasT);

	// 2 - Convert points Raster space
	// normalize x & y (set in [0,1] range)
	// Rasterised coordinates
	int x;
	int y;

	x = (int)(NDCout.x * p->width);
	y = (int)((1 - NDCout.y) * p->height);

	// We MAY still WANT draw the line to this point even
	// if it is outside the canvas, that's why we computed
	// it's position.
	if (out->x < p->canvasL || out->x > p->canvasR || out->y < p->canvasB || out->y > p->canvasT)

	{
		out->x = x;
		out->y = y;
		out->z = -in.z;
		return (1);
		//return (1);
	}
	out->x = x;
	out->y = y;
	out->z = -in.z;

	return (0);

	/*
	** OLD ALGORITHM
	out->x = (out->x + p->canvasW * .5f) / p->canvasW;
	out->y = (out->y + p->canvasH * .5f) / p->canvasH;
	// Multiply by framebuffer width & height
	out->x = floor(out->x * p->width);
	out->y = floor((1 - out->y) * p->width); // invert y
	*/
}

static int draw_point(t_mlx_sess *p, t_vec3f vertex, t_vec3f *point, t_mat4x4 *mvp)
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

	//
	// doesn't work'
	//if ((int)point->x < 0)
	//	point->x = 0;
	//else if ((int)point->x >= p->width)
	//	point->x = p->width;
	//if ((int)point->y < 0)
	//	point->y = 0;
	//else if ((int)point->y >= p->height)
	//	point->y = p->height;


	//if ((int)point->x < 0 || (int)point->x > p->width || (int)point->y < 0 || (int)point->y >= p->height)
	//	return (0);

	//draw_line((t_mlx_sess *)p, point, point);

	return (1);
}

//static void	draw_joints(t_mlx_sess *p, t_vec3f v, t_vec3f v2, t_mat4x4 *p->world, t_mat4x4 *W2C)
static void		draw_triangle(t_mlx_sess *p, t_tri *triangle, t_mat4x4 *mvp)
{
	t_vec3f	a;
	t_vec3f	b;
	t_vec3f	c;
	int a_test, b_test, c_test;
	t_vec3f	pixels[3];
	pixels[0].x = 0;
	pixels[0].y = 0;
	pixels[0].z = 0;
	pixels[1].x = 0;
	pixels[1].y = 0;
	pixels[1].z = 0;
	pixels[2].x = 0;
	pixels[2].y = 0;
	pixels[2].z = 0;

	a = (*triangle)[0].coord;
	b = (*triangle)[1].coord;
	c = (*triangle)[2].coord;

	a_test = draw_point(p, a, &pixels[0], mvp);
	b_test = draw_point(p, b, &pixels[1], mvp);
	c_test = draw_point(p, c, &pixels[2], mvp);

	// Coords are now in raster space
	t_tri t; // like t_vert[3];
	t[0].coord.x = pixels[0].x;
	t[0].coord.y = pixels[0].y;
	t[0].coord.z = pixels[0].z;
	// Divide vertex attribute by vertex z
	t[0].color.r = (*triangle)[0].color.r;
	t[0].color.g = (*triangle)[0].color.g;
	t[0].color.b = (*triangle)[0].color.b;

	t[1].coord.x = pixels[1].x;
	t[1].coord.y = pixels[1].y;
	t[1].coord.z = pixels[1].z;
	// Divide vertex attribute by vertex z
	t[1].color.r = (*triangle)[1].color.r;
	t[1].color.g = (*triangle)[1].color.g;
	t[1].color.b = (*triangle)[1].color.b;

	t[2].coord.x = pixels[2].x;
	t[2].coord.y = pixels[2].y;
	t[2].coord.z = pixels[2].z;
	// Divide vertex attribute by vertex z
	t[2].color.r = (*triangle)[2].color.r;
	t[2].color.g = (*triangle)[2].color.g;
	t[2].color.b = (*triangle)[2].color.b;

	// Pre-compute 1 over z
	//t[0].coord.z = 1 / t[0].coord.z;
	//t[1].coord.z = 1 / t[1].coord.z;
	//t[2].coord.z = 1 / t[2].coord.z;

	rasterize(p, &t);
	return ;

	t_vec2f	px[3];
	px[0].x = pixels[0].x;
	px[0].y = pixels[0].y;
	px[1].x = pixels[1].x;
	px[1].y = pixels[1].y;
	px[2].x = pixels[2].x;
	px[2].y = pixels[2].y;

	if (a_test || c_test)
	{
		if (a_test && b_test)
			p->col = 0x00ffffff;
		else
			p->col = 0x00ff0000;
		draw_line((t_mlx_sess *)p, &px[0], &px[1]);
	}
	if (b_test || c_test)
	{
		if (b_test && c_test)
			p->col = 0x00ffffff;
		else
			p->col = 0x00ff0000;
		draw_line((t_mlx_sess *)p, &px[1], &px[2]);
	}
	if (a_test || c_test)
	{
		if (a_test && c_test)
			p->col = 0x00ffffff;
		else
			p->col = 0x00ff0000;
		draw_line((t_mlx_sess *)p, &px[2], &px[0]);
	}
}

void	draw_3dgrid(t_mlx_sess *p)
{
//	static t_vec3f	from;
//	static t_vec3f	to;

	t_mat4x4	mvp;
	t_mat4x4	model;
	static t_mat4x4	*trans = NULL;
	static int r = 0;
	t_mat4x4	rot;
	t_mat4x4	tmp;
	t_vec3f s;
	t_vec3f o;
	//t_vec3f ox;
	//t_vec3f oy;
	//t_vec3f oz;

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
		trans = (t_mat4x4 *)malloc(sizeof(t_mat4x4));
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
	//t_mat4x4 iview;

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

//	while (x < 12)
//		draw_triangle(p, &p->cube[x++], &mvp);

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
