/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 12:41:37 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 20:05:43 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	Weighted-colors:
**	===============
**	r = w[0] * (*triangle)[0].color.r + w[1]
**		* (*triangle)[1].color.r + w[2] * (*triangle)[2].color.r;
**	g = w[0] * (*triangle)[0].color.g + w[1]
**		* (*triangle)[1].color.g + w[2] * (*triangle)[2].color.g;
**	b = w[0] * (*triangle)[0].color.b + w[1]
**		* (*triangle)[1].color.b + w[2] * (*triangle)[2].color.b;
*/

static void	set_buffer_pixel(t_mlx_sess *sess, t_vec2ui32 *xy,
								float z, float w[3])
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				col;

	col = sess->options.lines_color;
	if (sess->options.zdraw)
	{
		r = (unsigned char)(255 * z * 16);
		g = (unsigned char)(255 * z * 16);
		b = (unsigned char)(255 * z * 16);
		col = (r << 16) | (g << 8) | (b);
	}
	else if (w[0] >= sess->options.line_width
				&& w[1] >= sess->options.line_width && w[2] >= 0)
		col = sess->options.faces_color;
	sess->zbuffer[xy->x + xy->y * sess->width] = z;
	set_image_pixel(sess, sess->img, mlx_get_color_value(sess->sess, col), xy);
}

/*
**	Compute the edge function of the pixel and get it's weight
*/

static void	compute_pixel(t_mlx_sess *p,
							t_tri triangle, t_vec2ui32 *xy, float area)
{
	t_vec3f		pixel_sample;
	float		one_over_z;
	float		w[3];
	float		z;

	pixel_sample.x = xy->x;
	pixel_sample.y = xy->y;
	pixel_sample.z = 0;
	w[0] = EDGE_FN((triangle)[1].coord, (triangle)[2].coord, pixel_sample);
	w[1] = EDGE_FN((triangle)[2].coord, (triangle)[0].coord, pixel_sample);
	w[2] = EDGE_FN((triangle)[0].coord, (triangle)[1].coord, pixel_sample);
	if (w[0] >= 0.f && w[1] >= 0.f && w[2] >= 0.f)
	{
		w[0] /= area;
		w[1] /= area;
		w[2] /= area;
		one_over_z = (triangle)[0].coord.z * w[0]
				+ (triangle)[1].coord.z * w[1] + (triangle)[2].coord.z * w[2];
		z = one_over_z;
		if (z < p->zbuffer[xy->x + xy->y * p->width])
			set_buffer_pixel(p, xy, z, w);
	}
}

static int	compute_bb(t_mlx_sess *p,
						t_tri triangle, t_vec2ui32 *min, t_vec2ui32 *max)
{
	float	xmin;
	float	xmax;
	float	ymin;
	float	ymax;

	xmin = MIN3((triangle)[0].coord.x,
			(triangle)[1].coord.x, (triangle)[2].coord.x);
	xmax = MAX3((triangle)[0].coord.x,
			(triangle)[1].coord.x, (triangle)[2].coord.x);
	ymin = MIN3((triangle)[0].coord.y,
			(triangle)[1].coord.y, (triangle)[2].coord.y);
	ymax = MAX3((triangle)[0].coord.y,
			(triangle)[1].coord.y, (triangle)[2].coord.y);
	if (xmin > p->width - 1 || xmax < 0 || ymin > p->height - 1 || ymax < 0)
		return (0);
	min->x = (uint32_t)fmaxf(0.f, floorf(xmin));
	max->x = (uint32_t)fminf(p->width - 1, floorf(xmax));
	min->y = (uint32_t)fmaxf(0.f, floorf(ymin));
	max->y = (uint32_t)fminf(p->height - 1, floorf(ymax));
	return (1);
}

/*
**	Actually, the code doesn't check if the vertex
**	pass the top-left rule.
**	The test should be done just after the bb test
*/

void		rasterize(t_mlx_sess *p, t_tri *triangle)
{
	float		area;
	t_vec2ui32	min;
	t_vec2ui32	max;
	t_vec2ui32	xy;

	if (!compute_bb(p, *triangle, &min, &max))
		return ;
	area = EDGE_FN((*triangle)[0].coord,
					(*triangle)[1].coord, (*triangle)[2].coord);
	xy.y = min.y;
	while (xy.y < max.y)
	{
		xy.y++;
		xy.x = min.x;
		while (xy.x < max.x)
		{
			compute_pixel(p, *triangle, &xy, area);
			xy.x++;
		}
	}
}
