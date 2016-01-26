/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 20:00:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 02:52:44 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cube(t_triangle *cube)
{
	t_vector3 points[8];

	points[0].x = -.5f;
	points[0].y = -.5f;
	points[0].z = -.5f;
	points[1].x = .5f;
	points[1].y = -.5f;
	points[1].z = -.5f;
	points[2].x = .5f;
	points[2].y = .5f;
	points[2].z = -.5f;
	points[3].x = -.5f;
	points[3].y = .5f;
	points[3].z = -.5f;
	points[4].x = -.5f;
	points[4].y = -.5f;
	points[4].z = .5f;
	points[5].x = .5f;
	points[5].y = -.5f;
	points[5].z = .5f;
	points[6].x = .5f;
	points[6].y = .5f;
	points[6].z = .5f;
	points[7].x = -.5f;
	points[7].y = .5f;
	points[7].z = .5f;

	cube[0].a = points[0];
	cube[0].b = points[1];
	cube[0].c = points[3];
	cube[1].a = points[1];
	cube[1].b = points[2];
	cube[1].c = points[3];
	cube[2].a = points[1];
	cube[2].b = points[5];
	cube[2].c = points[2];
	cube[3].a = points[5];
	cube[3].b = points[6];
	cube[3].c = points[2];
	cube[4].a = points[5];
	cube[4].b = points[4];
	cube[4].c = points[6];
	cube[5].a = points[4];
	cube[5].b = points[7];
	cube[5].c = points[6];
	cube[6].a = points[4];
	cube[6].b = points[0];
	cube[6].c = points[7];
	cube[7].a = points[0];
	cube[7].b = points[3];
	cube[7].c = points[7];
	cube[8].a = points[3];
	cube[8].b = points[2];
	cube[8].c = points[7];
	cube[9].a = points[2];
	cube[9].b = points[6];
	cube[9].c = points[7];
	cube[10].a = points[0];
	cube[10].b = points[1];
	cube[10].c = points[4];
	cube[11].a = points[1];
	cube[11].b = points[5];
	cube[11].c = points[4];
}

void	init_grid_from_vertmap(t_grid *grid, t_vert **vertmap, int width, int height)
{
	int x;
	int y;
	int i;

	i = 0;
	x = 0;
	y = 0;
	grid->width = width;
	grid->height = height;
	grid->triangles = (t_triangle *)ft_memalloc(sizeof(t_triangle) * width * height * 2);
	while (x < width)
	{
		while (y < height)
		{
			grid->triangles[i].a.x = (float)(1.f * x);
			grid->triangles[i].a.y = (float)(1.f * y);
			grid->triangles[i].a.z = (float)vertmap[y][x].coord.z * 0.15f;
			grid->triangles[i].b.x = (float)(1.f * x + 1.f);
			grid->triangles[i].b.y = (float)(1.f * y);
			ft_putchar('@');
			ft_putnbr(x);
			ft_putchar('y');
			ft_putnbr(y);
			ft_putchar('#');
			ft_putnbr(width);
			ft_putchar('\n');
			if (x + 1 < width)
				grid->triangles[i].b.z = (float)vertmap[y][x + 1].coord.z * 0.15f;
			else
				grid->triangles[i].b.z = 0.f;
			grid->triangles[i].c.x = (float)(1.f * x);
			grid->triangles[i].c.y = (float)(1.f * y + 1.f);
			if (y + 1 < height)
				grid->triangles[i].c.z = (float)vertmap[y][x + 1].coord.z * 0.15f;
			else
				grid->triangles[i].c.z = 0.f;
			i++;

			grid->triangles[i].a.x = (float)(1.f * x + 1.f);
			grid->triangles[i].a.y = (float)(1.f * y);
			if (x + 1 < width)
				grid->triangles[i].a.z = (float)vertmap[y][x].coord.z * 0.15f;
			else
				grid->triangles[i].a.z = 0.f;
			grid->triangles[i].b.x = (float)(1.f * x + 1.f);
			grid->triangles[i].b.y = (float)(1.f * y + 1.f);
			if (x + 1 < width && y + 1 < height)
				grid->triangles[i].b.z = (float)vertmap[y + 1][x].coord.z * 0.15f;
			else
				grid->triangles[i].b.z = 0.f;
			grid->triangles[i].c.x = (float)(1.f * x);
			grid->triangles[i].c.y = (float)(1.f * y + 1.f);
			if (y + 1 < height)
				grid->triangles[i].c.z = (float)vertmap[y][x + 1].coord.z * 0.15f;
			else
				grid->triangles[i].c.z = 0.f;
			i++;
			y++;
		}
		y = 0;
		x++;
	}

}

void	init_grid(t_grid *grid, int width, int height)
{
	int		x;
	int		y;
	int		i;

	x = 0;
	y = 0;
	i = 0;
	grid->width = width;
	grid->height = height;

	// The number of triangles in the grid is
	// faces * 2
	// which is equals to
	// (width * height) * 2
	grid->triangles = (t_triangle *)malloc(sizeof(t_triangle) * width * height * 2);
	while (x < width)
	{
		while(y < height)
		{
			grid->triangles[i].a.x = (float)(1.f * x);
			grid->triangles[i].a.y = (float)(1.f * y);
			grid->triangles[i].a.z = 0.f;
			grid->triangles[i].b.x = (float)(1.f * x + 1.f);
			grid->triangles[i].b.y = (float)(1.f * y);
			grid->triangles[i].b.z = 0.f;
			grid->triangles[i].c.x = (float)(1.f * x);
			grid->triangles[i].c.y = (float)(1.f * y + 1.f);
			grid->triangles[i].c.z = 0.f;
			i++;

			grid->triangles[i].a.x = (float)(1.f * x + 1.f);
			grid->triangles[i].a.y = (float)(1.f * y);
			grid->triangles[i].a.z = 0.f;
			grid->triangles[i].b.x = (float)(1.f * x + 1.f);
			grid->triangles[i].b.y = (float)(1.f * y + 1.f);
			grid->triangles[i].b.z = 0.f;
			grid->triangles[i].c.x = (float)(1.f * x);
			grid->triangles[i].c.y = (float)(1.f * y + 1.f);
			grid->triangles[i].c.z = 0.f;
			i++;
			y++;
		}
		y = 0;
		x++;
	}
}
