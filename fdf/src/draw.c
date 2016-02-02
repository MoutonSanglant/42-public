/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:35:36 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/01 17:18:49 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_mlx_sess *p, t_vec2f *from, t_vec2f *to)
{
	t_image	*img;
	int x1 = (int)from->x;
	int x2 = (int)to->x;
	int y1 = (int)from->y;
	int y2 = (int)to->y;
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;
	int color;

	color = mlx_get_color_value(p->sess, p->col);

	dx = x2 - x1;
	dy = y2 - y1;

	if(dx < 0) dx = -dx;
	if(dy < 0) dy = -dy;
	incx = 1;
	if(x2 < x1) incx = -1;
	incy = 1;
	if(y2 < y1) incy = -1;
	x=x1;
	y=y1;

	img = p->img;

	if(dx > dy)
	{
		set_image_pixel(p, img, color, x, y);
		e = 2*dy - dx;
		inc1 = 2*( dy -dx);
		inc2 = 2*dy;
		for(i = 0; i < dx; i++)
		{
			if(e >= 0)
			{
				y += incy;
				e += inc1;
			}
			else e += inc2;
				x += incx;
			set_image_pixel(p, img, color, x, y);
		}
	}
	else
	{
		set_image_pixel(p, img, color, x, y);
		e = 2*dx - dy;
		inc1 = 2*( dx - dy);
		inc2 = 2*dx;
		for(i = 0; i < dy; i++)
		{
			if(e >= 0)
			{
				x += incx;
				e += inc1;
			}
			else e += inc2;
				y += incy;
			set_image_pixel(p, img, color, x, y);
		}
	}

}

void	clear_canvas(t_mlx_sess *p, int clear_color)
{
	size_t x;
	size_t y;

	x = 0;
	y = 0;
	while (x < p->width)
	{
		while (y < p->height)
		{
			set_image_pixel(p, p->img, clear_color, x, y++);
			p->zbuffer[x + y * (p->width - 1) ] = FLT_MAX;
		}
		y = 0;
		x++;
	}
}

void	draw_square(t_mlx_sess *p, int color, t_vec2f *from, t_vec2f *to)
{
	int		x;
	int		y;

	x = from->x;
	y = from->y;
	while (x < to->x)
	{
		while (y < to->y)
		{
			set_image_pixel(p, p->img, color, x, y++);
		}
		y = from->y;
		x++;
	}
}

void	draw_pixel_chain(t_mlx_sess *mlx_sess)
{
	static int	x = 0;
	static int	y = 0;
	static int	r = 0;
	static int	g = 0;
	static int	b = 0;
	int			c;

	c = r | g | b;
	mlx_pixel_put(mlx_sess->sess, mlx_sess->win, x, y, c);
	mlx_pixel_put(mlx_sess->sess, mlx_sess->win, x + 1, y, c);
	mlx_pixel_put(mlx_sess->sess, mlx_sess->win, x, y + 1, c);
	mlx_pixel_put(mlx_sess->sess, mlx_sess->win, x + 1, y + 1, c);
	x += 2;
	if (x >= 199)
	{
		y += 2;
		x = 0;
		if (y >= 199)
			y = 0;
	}
	r += 0x00000001;
	g += 0x00000200;
	b += 0x00080000;
}

void	draw_image(t_mlx_sess *mlx_sess, void *img, int *x, int *y)
{
	//static void		*img = 0;

	mlx_put_image_to_window(mlx_sess->sess, mlx_sess->win, img, *x, *y);
	mlx_string_put(mlx_sess->sess, mlx_sess->win, 0, 0, 0x00ff0000, "Hello");
}
