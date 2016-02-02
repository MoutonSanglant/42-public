/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 20:00:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/01 20:03:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cube(t_tri *cube)
{
	t_vec3f points[8];

	// A
	points[0].x = -.5f;
	points[0].y = -.5f;
	points[0].z = -.5f;
	// B
	points[1].x = .5f;
	points[1].y = -.5f;
	points[1].z = -.5f;
	// C
	points[2].x = .5f;
	points[2].y = .5f;
	points[2].z = -.5f;
	// D
	points[3].x = -.5f;
	points[3].y = .5f;
	points[3].z = -.5f;
	// E
	points[4].x = -.5f;
	points[4].y = -.5f;
	points[4].z = .5f;
	// F
	points[5].x = .5f;
	points[5].y = -.5f;
	points[5].z = .5f;
	// G
	points[6].x = .5f;
	points[6].y = .5f;
	points[6].z = .5f;
	// H
	points[7].x = -.5f;
	points[7].y = .5f;
	points[7].z = .5f;

	cube[0][0].coord = points[1];
	cube[0][1].coord = points[3];
	cube[0][2].coord = points[0];
	cube[1][0].coord = points[1];
	cube[1][1].coord = points[2];
	cube[1][2].coord = points[3];

	cube[2][0].coord = points[5];
	cube[2][1].coord = points[2];
	cube[2][2].coord = points[1];
	cube[3][0].coord = points[5];
	cube[3][1].coord = points[6];
	cube[3][2].coord = points[2];

	cube[4][0].coord = points[4];
	cube[4][1].coord = points[6];
	cube[4][2].coord = points[5];
	cube[5][0].coord = points[4];
	cube[5][1].coord = points[7];
	cube[5][2].coord = points[6];

	cube[6][0].coord = points[0];
	cube[6][1].coord = points[7];
	cube[6][2].coord = points[4];
	cube[7][0].coord = points[0];
	cube[7][1].coord = points[3];
	cube[7][2].coord = points[7];

	cube[8][0].coord = points[2];
	cube[8][1].coord = points[7];
	cube[8][2].coord = points[3];
	cube[9][0].coord = points[2];
	cube[9][1].coord = points[6];
	cube[9][2].coord = points[7];

	cube[10][0].coord = points[1];
	cube[10][1].coord = points[0];
	cube[10][2].coord = points[4];
	cube[11][0].coord = points[1];
	cube[11][1].coord = points[4];
	cube[11][2].coord = points[5];
}

void	change_grid_z_value(t_grid *grid, float f)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	l = grid->width * grid->height * 2;
	while (i < l)
	{
		j = 0;
		while (j < 3)
			grid->triangles[i][j++].coord.z *= f;
		i++;
	}
}

void	init_grid_from_vertmap(t_grid *grid, t_vert **vertmap, int width, int height)
{
	int x;
	int y;
	int i;

	unsigned char r;
	unsigned char g;
	unsigned char b;

	char x_diff;
	char y_diff;

	r = 0;
	g = 0;
	b = 0;
	i = 0;
	x = 0;
	y = 0;
	x_diff = 255 / width;
	y_diff = 255 / height;
	grid->width = width;
	grid->height = height;
	grid->triangles = (t_tri *)ft_memalloc(sizeof(t_tri) * width * height * 2);
	while (x < width)
	{
		g = 0;
		while (y < height)
		{
			// top-right triangle
			grid->triangles[i][0].color.r = r + x_diff;
			grid->triangles[i][0].color.g = g + y_diff;
			grid->triangles[i][0].color.b = b;
			grid->triangles[i][1].color.r = r;
			grid->triangles[i][1].color.g = g;
			grid->triangles[i][1].color.b = b;
			grid->triangles[i][2].color.r = r;
			grid->triangles[i][2].color.g = g + y_diff;
			grid->triangles[i][2].color.b = b;

			// bottom-left triangle
			grid->triangles[i + 1][0].color.r = r + x_diff;
			grid->triangles[i + 1][0].color.g = g + y_diff;
			grid->triangles[i + 1][0].color.b = b;
			grid->triangles[i + 1][1].color.r = r + x_diff;
			grid->triangles[i + 1][1].color.g = g;
			grid->triangles[i + 1][1].color.b = b;
			grid->triangles[i + 1][2].color.r = r;
			grid->triangles[i + 1][2].color.g = g;
			grid->triangles[i + 1][2].color.b = b;
			g += y_diff;
			b = r * .5f + g * .5f;

			/*
			** +x <-
			** +y ^
			**
			** 1
			** | \
			** 2--0
			**
			** 2--1
			**  \ |
			**    0
			**
			** ccw
			**
			** according to camera:
			** 0--2
			**  \ |
			**    1
			**
			** 0
			** | \
			** 1--2
			**
			*/

			grid->triangles[i][0].coord.x = (float)(1.f * x + 1.f);
			grid->triangles[i][0].coord.y = (float)(1.f * y + 1.f);
			if (x + 1 < width && y + 1 < height)
				grid->triangles[i][0].coord.z = (float)vertmap[y + 1][x + 1].coord.z * 0.15f;
			else
				grid->triangles[i][0].coord.z = 0.f;
			grid->triangles[i][1].coord.x = (float)(1.f * x);
			grid->triangles[i][1].coord.y = (float)(1.f * y);
			grid->triangles[i][1].coord.z = (float)vertmap[y][x].coord.z * 0.15f;
			grid->triangles[i][2].coord.x = (float)(1.f * x);
			grid->triangles[i][2].coord.y = (float)(1.f * y + 1.f);
			if (y + 1 < height)
				grid->triangles[i][2].coord.z = (float)vertmap[y + 1][x].coord.z * 0.15f;
			else
				grid->triangles[i][2].coord.z = 0.f;
			i++;

			grid->triangles[i][0].coord.x = (float)(1.f * x + 1.f);
			grid->triangles[i][0].coord.y = (float)(1.f * y + 1.f);
			if (x + 1 < width && y + 1 < height)
				grid->triangles[i][0].coord.z = (float)vertmap[y + 1][x + 1].coord.z * 0.15f;
			else
				grid->triangles[i][0].coord.z = 0.f;
			grid->triangles[i][1].coord.x = (float)(1.f * x + 1.f);
			grid->triangles[i][1].coord.y = (float)(1.f * y);
			if (x + 1 < width)
				grid->triangles[i][1].coord.z = (float)vertmap[y][x + 1].coord.z * 0.15f;
			else
				grid->triangles[i][1].coord.z = 0.f;
			grid->triangles[i][2].coord.x = (float)(1.f * x);
			grid->triangles[i][2].coord.y = (float)(1.f * y);
			grid->triangles[i][2].coord.z = (float)vertmap[y][x].coord.z * 0.15f;
			i++;
			y++;
		}
		r += x_diff;
		y = 0;
		x++;
	}
}

void	init_grid(t_grid *grid, int width, int height)
{
	int		x;
	int		y;
	int		i;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	char x_diff;
	char y_diff;

	r = 0;
	g = 0;
	b = 0;

	x_diff = 255 / width;
	y_diff = 255 / height;
	ft_putchar('*');
	ft_putnbr(x_diff);
	ft_putchar('\n');

	x = 0;
	y = 0;
	i = 0;
	grid->width = width;
	grid->height = height;

	// The number of triangles in the grid is
	// faces * 2
	// which is equals to
	// (width * height) * 2
	grid->triangles = (t_tri *)malloc(sizeof(t_tri) * width * height * 2);
	while (x < width)
	{
		g = 0;
		while(y < height)
		{
			// top-right triangle
			grid->triangles[i][0].color.r = r + x_diff;
			grid->triangles[i][0].color.g = g + y_diff;
			grid->triangles[i][0].color.b = b;
			grid->triangles[i][1].color.r = r;
			grid->triangles[i][1].color.g = g;
			grid->triangles[i][1].color.b = b;
			grid->triangles[i][2].color.r = r;
			grid->triangles[i][2].color.g = g + y_diff;
			grid->triangles[i][2].color.b = b;

			// bottom-left triangle
			grid->triangles[i + 1][0].color.r = r + x_diff;
			grid->triangles[i + 1][0].color.g = g + y_diff;
			grid->triangles[i + 1][0].color.b = b;
			grid->triangles[i + 1][1].color.r = r + x_diff;
			grid->triangles[i + 1][1].color.g = g;
			grid->triangles[i + 1][1].color.b = b;
			grid->triangles[i + 1][2].color.r = r;
			grid->triangles[i + 1][2].color.g = g;
			grid->triangles[i + 1][2].color.b = b;
			g += y_diff;
			b = r * .5f + g * .5f;

			grid->triangles[i][0].coord.x = (float)(1.f * x + 1.f);
			grid->triangles[i][0].coord.y = (float)(1.f * y + 1.f);
			grid->triangles[i][0].coord.z = 0.f;
			grid->triangles[i][1].coord.x = (float)(1.f * x);
			grid->triangles[i][1].coord.y = (float)(1.f * y);
			grid->triangles[i][1].coord.z = 0.f;
			grid->triangles[i][2].coord.x = (float)(1.f * x);
			grid->triangles[i][2].coord.y = (float)(1.f * y + 1.f);
			grid->triangles[i][2].coord.z = 0.f;
			i++;

			grid->triangles[i][0].coord.x = (float)(1.f * x + 1.f);
			grid->triangles[i][0].coord.y = (float)(1.f * y + 1.f);
			grid->triangles[i][0].coord.z = 0.f;
			grid->triangles[i][1].coord.x = (float)(1.f * x + 1.f);
			grid->triangles[i][1].coord.y = (float)(1.f * y);
			grid->triangles[i][1].coord.z = 0.f;
			grid->triangles[i][2].coord.x = (float)(1.f * x);
			grid->triangles[i][2].coord.y = (float)(1.f * y);
			grid->triangles[i][2].coord.z = 0.f;
			i++;
			y++;
		}
		r += x_diff;
		y = 0;
		x++;
	}
}
