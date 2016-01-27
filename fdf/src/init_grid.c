/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 20:00:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/27 21:59:42 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cube(t_tri *cube)
{
	t_vec3f points[8];

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

	cube[0][0] = points[0];
	cube[0][1] = points[1];
	cube[0][2] = points[3];
	cube[1][0] = points[1];
	cube[1][1] = points[2];
	cube[1][2] = points[3];
	cube[2][0] = points[1];
	cube[2][1] = points[5];
	cube[2][2] = points[2];
	cube[3][0] = points[5];
	cube[3][1] = points[6];
	cube[3][2] = points[2];
	cube[4][0] = points[5];
	cube[4][1] = points[4];
	cube[4][2] = points[6];
	cube[5][0] = points[4];
	cube[5][1] = points[7];
	cube[5][2] = points[6];
	cube[6][0] = points[4];
	cube[6][1] = points[0];
	cube[6][2] = points[7];
	cube[7][0] = points[0];
	cube[7][1] = points[3];
	cube[7][2] = points[7];
	cube[8][0] = points[3];
	cube[8][1] = points[2];
	cube[8][2] = points[7];
	cube[9][0] = points[2];
	cube[9][1] = points[6];
	cube[9][2] = points[7];
	cube[10][0] = points[0];
	cube[10][1] = points[1];
	cube[10][2] = points[4];
	cube[11][0] = points[1];
	cube[11][1] = points[5];
	cube[11][2] = points[4];
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
	grid->triangles = (t_tri *)ft_memalloc(sizeof(t_tri) * width * height * 2);
	while (x < width)
	{
		while (y < height)
		{
			grid->triangles[i][0].x = (float)(1.f * x);
			grid->triangles[i][0].y = (float)(1.f * y);
			grid->triangles[i][0].z = (float)vertmap[y][x].coord.z * 0.15f;
			grid->triangles[i][1].x = (float)(1.f * x + 1.f);
			grid->triangles[i][1].y = (float)(1.f * y);
			if (x + 1 < width)
				grid->triangles[i][1].z = (float)vertmap[y][x + 1].coord.z * 0.15f;
			else
				grid->triangles[i][1].z = 0.f;
			grid->triangles[i][2].x = (float)(1.f * x);
			grid->triangles[i][2].y = (float)(1.f * y + 1.f);
			if (y + 1 < height)
				grid->triangles[i][2].z = (float)vertmap[y][x + 1].coord.z * 0.15f;
			else
				grid->triangles[i][2].z = 0.f;
			i++;

			grid->triangles[i][0].x = (float)(1.f * x + 1.f);
			grid->triangles[i][0].y = (float)(1.f * y);
			if (x + 1 < width)
				grid->triangles[i][0].z = (float)vertmap[y][x].coord.z * 0.15f;
			else
				grid->triangles[i][0].z = 0.f;
			grid->triangles[i][1].x = (float)(1.f * x + 1.f);
			grid->triangles[i][1].y = (float)(1.f * y + 1.f);
			if (x + 1 < width && y + 1 < height)
				grid->triangles[i][1].z = (float)vertmap[y + 1][x].coord.z * 0.15f;
			else
				grid->triangles[i][1].z = 0.f;
			grid->triangles[i][2].x = (float)(1.f * x);
			grid->triangles[i][2].y = (float)(1.f * y + 1.f);
			if (y + 1 < height)
				grid->triangles[i][2].z = (float)vertmap[y][x + 1].coord.z * 0.15f;
			else
				grid->triangles[i][2].z = 0.f;
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
	grid->triangles = (t_tri *)malloc(sizeof(t_tri) * width * height * 2);
	while (x < width)
	{
		while(y < height)
		{
			grid->triangles[i][0].x = (float)(1.f * x + 1.f);
			grid->triangles[i][0].y = (float)(1.f * y + 1.f);
			grid->triangles[i][0].z = 0.f;
			grid->triangles[i][1].x = (float)(1.f * x);
			grid->triangles[i][1].y = (float)(1.f * y);
			grid->triangles[i][1].z = 0.f;
			grid->triangles[i][2].x = (float)(1.f * x);
			grid->triangles[i][2].y = (float)(1.f * y + 1.f);
			grid->triangles[i][2].z = 0.f;
			i++;

			grid->triangles[i][0].x = (float)(1.f * x + 1.f);
			grid->triangles[i][0].y = (float)(1.f * y + 1.f);
			grid->triangles[i][0].z = 0.f;
			grid->triangles[i][1].x = (float)(1.f * x + 1.f);
			grid->triangles[i][1].y = (float)(1.f * y);
			grid->triangles[i][1].z = 0.f;
			grid->triangles[i][2].x = (float)(1.f * x);
			grid->triangles[i][2].y = (float)(1.f * y);
			grid->triangles[i][2].z = 0.f;
			i++;
			y++;
		}
		y = 0;
		x++;
	}
}
