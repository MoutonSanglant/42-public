/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dgrid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:52:02 by tdefresn          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2016/01/29 21:00:13 by tdefresn         ###   ########.fr       */
=======
/*   Updated: 2016/01/29 04:52:26 by tdefresn         ###   ########.fr       */
>>>>>>> 971e4bd1b61cb66c1fb64c09f24246ee52b1502a
=======
/*   Updated: 2016/01/30 04:34:32 by tdefresn         ###   ########.fr       */
>>>>>>> 454ed62... fdf perspective & orthographic projection matrices
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

/*
static int		rasterize_coord(t_mlx_sess *p, t_vec3f in, t_vec3f *out)
{
	t_vec3f NDCout;

	// This is a point in Camera space
	out->x = in.x / -in.z * p->near; // we need to multiply x by near
	out->y = in.y / -in.z * p->near; // we need to multiply y by near

	// 1 - Convert point to NDC space
	// NDC space should be in range [-1, 1] (GPU convention)

	//int r, l, t, b;
	//r = p->canvasR;
	//t = p->canvasT;
	//l = p->canvasL;
	//b = p->canvasB;
	//NDCout.x = 2 * out->x / (r - l) - (r + l) / (r - l); //!! NEXT LESSON !!
	//NDCout.y = 2 * out->y / (t - b) - (t + b) / (t - b); //!! NEXT LESSON !!

	NDCout.x = (out->x + p->canvasR) / (2 * p->canvasR);
	NDCout.y = (out->y + p->canvasT) / (2 * p->canvasT);

	// 2 - Convert point to Raster space
	// normalize x & y (set in [0,1] range)
	// Rasterised coordinates
	int x;
	int y;

	x = (int)(NDCout.x * p->width);
	y = (int)((1 - NDCout.y) * p->height);

	// We MAY still WANT draw the line to this point even
	// if it is outside the canvas, that's why we computed
	// it's position.
	out->x = x;
	out->y = y;
	out->z = -in.z;

	// Not working:
	if (out->x < p->canvasL || out->x > p->canvasR || out->y < p->canvasB || out->y > p->canvasT)
		return (1);
	return (0);
}
/*/
static int compute_point(t_mlx_sess *p, t_vec3f vertex, t_vec3f *point)
{
	*point = apply_matrix4(vertex, p->projection);

	if (point->x < -1.f || point->x > 1.f || point->y < -1.f || point->x > 1.f)
	{
		// point is outside the screen, we need to
		// make 2 new triangles in order to draw
		// the surface
		return (0);
	}

	point->x = fminf(p->width - 1.f, ((uint32_t)((point->x + 1.f) * 0.5f * p->width)));
	point->y = fminf(p->height - 1.f, ((uint32_t)((1.f - (point->y + 1.f) * 0.5f) * p->height)));
	point->z = -vertex.z;

	//point->x = ((uint32_t)((point->x + 1.f) * 0.5f * p->width));
	//point->y = ((uint32_t)((1.f - (point->y + 1.f) * 0.5f) * p->height));

	return (1);
}
//*/

static void		draw_triangle(t_mlx_sess *p, t_tri *triangle, t_mat4x4 *mvp)
{
	int		i;

	t_tri	t; // like t_vert[3];
	t_vec3f	a[3];
	t_vec3f	pixels[3];
	//t_vec2f	px[3];
	int		test[3];


	i = 0;
	while (i < 3)
	{
		pixels[i].x = 0;
		pixels[i].y = 0;
		pixels[i].z = 0;

		a[i] = (*triangle)[i].coord;
		// Transformation matrix = world * view * projection;
		a[i] = apply_matrix4(a[i], mvp);
		a[i] = apply_matrix4(a[i], p->worldToCamera);
		test[i] = compute_point(p, a[i], &pixels[i]);
		//test[i] = rasterize_coord(p, a[i], &pixels[i]);

		// Coords are now in raster space
		t[i].coord.x = pixels[i].x;
		t[i].coord.y = pixels[i].y;
		t[i].coord.z = pixels[i].z;

		// NOT WORKING: Divide vertex attribute by vertex z
		// set vectex attribute
		t[i].color.r = (*triangle)[i].color.r;
		t[i].color.g = (*triangle)[i].color.g;
		t[i].color.b = (*triangle)[i].color.b;

		// Pre-compute 1 over z
		t[i].coord.z = 1 / t[i].coord.z;

		// pixels for line draw
		//px[i].x = pixels[i].x;
		//px[i].y = pixels[i].y;

		i++;
	}

	if (test[0] && test[1] && test[2])
	{
		rasterize(p, &t);

		/*
		if (test[0] && test[1])
			draw_line((t_mlx_sess *)p, &px[0], &px[1]);
		if (test[1] && test[2])
			draw_line((t_mlx_sess *)p, &px[1], &px[2]);
		if (test[0] && test[2])
			draw_line((t_mlx_sess *)p, &px[0], &px[2]);
		*/
	}
	//return ;

}

void	draw_3dgrid(t_mlx_sess *p)
{
	t_mat4x4	mvp;
	t_mat4x4	model;

	identity_matrix4(&model);

	// Add model transformations here...
	//t_mat4x4	tmp;

	// Enable to rotate the model
	/*
	static int r = 0;
	t_mat4x4	rot;

	rotationZ_matrix4(&rot, RAD(r));
	matrix4_product(&model, &rot);
	r += 5;
	*/

	// Model Matrix: Local
	identity_matrix4(&mvp);
	matrix4_product(&mvp, &model);
	// World (local-to-world)
	matrix4_product(&mvp, p->world);

	int		i;
	int		x = 0;
	int		y = 0;

	// Draw a small cube
	p->col = 0x00ff0000;
	while (x < 12)
		draw_triangle(p, &p->cube[x++], &mvp);

	// Draw the grid
	i = 0;
	x = 0;
	p->col = 0x00ffffff;
	while (x < p->grid->width)
	{
		while (y < p->grid->height)
		{
			draw_triangle(p, &p->grid->triangles[i++], &mvp);
			draw_triangle(p, &p->grid->triangles[i++], &mvp);
			y++;
		}
		y = 0;
		x++;
	}
}
