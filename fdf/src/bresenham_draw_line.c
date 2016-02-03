/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_draw_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:53:27 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/03 16:59:00 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		bresenham_init(t_bresenham *bres)
{
	bres->dx = bres->x2 - bres->x1;
	bres->dy = bres->y2 - bres->y1;
	if (bres->dx < 0)
		bres->dx = -bres->dx;
	if (bres->dy < 0)
		bres->dy = -bres->dy;
	bres->incx = 1;
	if (bres->x2 < bres->x1)
		bres->incx = -1;
	bres->incy = 1;
	if (bres->y2 < bres->y1)
		bres->incy = -1;
	bres->x = bres->x1;
	bres->y = bres->y1;
}

static void		bresenham_x_bigger_than_y(t_bresenham *bres, t_mlx_sess *sess,
											t_image *img, int color)
{
	int			i;

	set_image_pixel(sess, img, color, bres->x, bres->y);
	bres->e = 2 * bres->dy - bres->dx;
	bres->inc1 = 2 * (bres->dy - bres->dx);
	bres->inc2 = 2 * bres->dy;
	i = 0;
	while (i < bres->dx)
	{
		if (bres->e >= 0)
		{
			bres->y += bres->incy;
			bres->e += bres->inc1;
		}
		else
			bres->e += bres->inc2;
		bres->x += bres->incx;
		set_image_pixel(sess, img, color, bres->x, bres->y);
		i++;
	}
}

static void		bresenham_y_bigger_than_x(t_bresenham *bres, t_mlx_sess *sess,
											t_image *img, int color)
{
	int			i;

	set_image_pixel(sess, img, color, bres->x, bres->y);
	bres->e = 2 * bres->dx - bres->dy;
	bres->inc1 = 2 * (bres->dx - bres->dy);
	bres->inc2 = 2 * bres->dx;
	i = 0;
	while (i < bres->dy)
	{
		if (bres->e >= 0)
		{
			bres->x += bres->incx;
			bres->e += bres->inc1;
		}
		else
			bres->e += bres->inc2;
		bres->y += bres->incy;
		set_image_pixel(sess, img, color, bres->x, bres->y);
		i++;
	}
}

void			bresenham_draw_line(t_mlx_sess *sess, t_vec2 *from, t_vec2 *to)
{
	t_bresenham	bres;
	int			color;

	color = mlx_get_color_value(sess->sess, sess->col);
	bres.x1 = from->x;
	bres.x2 = to->x;
	bres.y1 = from->y;
	bres.y2 = to->y;
	bresenham_init(&bres);
	if (bres.dx > bres.dy)
		bresenham_x_bigger_than_y(&bres, sess, sess->img, color);
	else
		bresenham_y_bigger_than_x(&bres, sess, sess->img, color);
}
