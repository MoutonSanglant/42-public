/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 12:41:37 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/03 20:41:42 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <limits.h>

static float	edge_function(const t_vec3f *a, const t_vec3f *b, const t_vec3f *c)
{
	return ((c->x - a->x) * (b->y - a->y) - (c->y - a->y) * (b->x - a->x));
}

static float	min3(const float *a, const float *b, const float *c)
{
	return (fminf(*a, fminf(*b, *c)));
}

static float	max3(const float *a, const float *b, const float *c)
{
	return (fmaxf(*a, fmaxf(*b, *c)));
}

void		rasterize(t_mlx_sess *p, t_tri *triangle)
{
	float	area;
	float xmin;
	float xmax;
	float ymin;
	float ymax;

	// get bouding box of the triangle
	xmin = min3(&(*triangle)[0].coord.x, &(*triangle)[1].coord.x, &(*triangle)[2].coord.x);
	xmax = max3(&(*triangle)[0].coord.x, &(*triangle)[1].coord.x, &(*triangle)[2].coord.x);
	ymin = min3(&(*triangle)[0].coord.y, &(*triangle)[1].coord.y, &(*triangle)[2].coord.y);
	ymax = max3(&(*triangle)[0].coord.y, &(*triangle)[1].coord.y, &(*triangle)[2].coord.y);

	if (xmin > p->width - 1 || xmax < 0 || ymin > p->height - 1 || ymax < 0)
		return ;

	uint32_t x0 = (uint32_t)fmaxf(0.f, (float) floor(xmin));
	uint32_t x1 = (uint32_t)fminf(p->width - 1, (float) floor(xmax));
	uint32_t y0 = (uint32_t)fmaxf(0.f, (float) floor(ymin));
	uint32_t y1 = (uint32_t)fminf(p->height - 1, (float) floor(ymax));

	// check if vertex pass the top-left rule
	// - not implemented

	//triangle[0] = ...;
	//triangle[1] = ...;
	//triangle[2] = ...;

	area = edge_function(&(*triangle)[0].coord, &(*triangle)[1].coord, &(*triangle)[2].coord); // area of the full triangle * 2

	uint32_t x, y;
	y = y0;
	while (y < y1)
	{
		y++;
		x = x0;
		while (x < x1)
		{
			t_vec3f pixel_sample;
			float	w[3];

			x++;
			pixel_sample.x = x;
			pixel_sample.y = y;
			pixel_sample.z = 0;

			w[0] = edge_function(&(*triangle)[1].coord, &(*triangle)[2].coord, &pixel_sample); // signed area of the small triangle * 2
			w[1] = edge_function(&(*triangle)[2].coord, &(*triangle)[0].coord, &pixel_sample);
			w[2] = edge_function(&(*triangle)[0].coord, &(*triangle)[1].coord, &pixel_sample);

			if (w[0] >= 0.f && w[1] >= 0.f && w[2] >= 0.f)
			{
				float z;
				float oneOverZ;

				w[0] /= area;
				w[1] /= area;
				w[2] /= area;

				oneOverZ = (*triangle)[0].coord.z * w[0] + (*triangle)[1].coord.z * w[1] + (*triangle)[2].coord.z * w[2];
				//z = 1 / oneOverZ;
				z = oneOverZ;
				if (z < p->zbuffer[x + y * p->width])
				{
					unsigned char r = w[0] * (*triangle)[0].color.r + w[1] * (*triangle)[1].color.r + w[2] * (*triangle)[2].color.r;
					unsigned char g = w[0] * (*triangle)[0].color.g + w[1] * (*triangle)[1].color.g + w[2] * (*triangle)[2].color.g;
					unsigned char b = w[0] * (*triangle)[0].color.b + w[1] * (*triangle)[1].color.b + w[2] * (*triangle)[2].color.b;

					// Visual render of the z-Buffer
					//r = (unsigned char) 255 * z * 4;
					//g = (unsigned char) 255 * z * 4;
					//b = (unsigned char) 255 * z * 4;

					int col = (r << 16) | (g << 8) | (b);
					//if (w[0] > .59f || w[1] > .59f || w[2] > .59f)
					//	col = 0x00046000;

					col = p->lines_color;
					if (w[0] >= p->line_width && w[1] >= 0 && w[2] >= 0)
						col = p->faces_color;
					p->zbuffer[x + y * p->width] = z;
					t_vec2ui32	xy;
					xy.x = x;
					xy.y = y;
					set_image_pixel(p, p->img, mlx_get_color_value(p->sess, col), xy);
				}
			}
		}
	}
}
