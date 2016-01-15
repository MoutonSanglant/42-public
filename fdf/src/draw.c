#include "fdf.h"

void	draw_line(t_mlx_sess *mlx, t_vector2 *from, t_vector2 *to)
{
	int x1 = from->x;
	int x2 = to->x;
	int y1 = from->y;
	int y2 = to->y;
  int dx, dy, i, e;
  int incx, incy, inc1, inc2;
  int x,y;

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

  if(dx > dy)
    {
      //draw_pixel(x,y, BLACK);
		mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
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
        // draw_pixel(x,y, BLACK);
		mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
      }
   }
   else
   {
      //draw_pixel(x,y, BLACK);
		mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
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
        //draw_pixel(x,y, BLACK);
		mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
    }
  }

}

//void	draw_line(t_mlx_sess *mlx, t_vector3 from, t_vector3 to)
/*
void	draw_line(t_mlx_sess *mlx, t_vector2 *from, t_vector2 *to)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		e;

	x = from->x;
	y = from->y;
	dx = to->x - x;
	if (dx)
	{
		if (dx > 0)
		{
			if ((dy = to->y - from->y))
			{
				if (dy > 0)
				{
					if (dx >= dy)
					{
						e = dx;
						dx = e * 2;
						dy = dy * 2;
						x = from->x;
						y = from->y;
						while (1)
						{
							mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
							x = x + 1;
							if (x == to->x)
								break ;
							e = e - dy;
							if (e < 0)
							{
								y = y + 1;
								e = e + dx;
							}
						}
					}
					else
					{
						e = dy;
						dy = e * 2;
						dx = dx * 2;
						x = from->x;
						y = from->y;
						while (1)
						{
							mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
							//x = x + 1;
							y = y + 1;
							if (y == to->y)
								break ;
							e = e - dx;
							if (e < 0)
							{
								x = x + 1;
								e = e + dy;
							}
						}
					}
				}
				else
				{
					if (dx >= -dy)
					{
						e = dx;
						dx = e * 2;
						dy = dy * 2;
						x = from->x;
						y = from->y;
						while (1)
						{
							mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
							x = x + 1;
							if (x == to->x)
								break ;
							e = e + dy;
							if (e < 0)
							{
								y = y - 1;
								e = e + dx;
							}
						}
					}
					else
					{
						e = dy;
						dy = e * 2;
						dx = dx * 2;
						x = from->x;
						y = from->y;
						while (1)
						{
							mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
							y = y - 1;
							if (y == to->y)
								break ;
							e = e + dx;
							if (e > 0)
							{
								x = x + 1;
								e = e + dy;
							}
						}
					}
				}
			}
			else
			{
				y = from->y;
				while (x != to->x)
				{
					mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
					x = x + 1;
				}
			}
		}
		else
		{
			if ((dy = to->y - from->y))
			{
				if (dy > 0)
				{
					if (-dx >= dy)
					{
						e = dx;
						dx = e * 2;
						dy = dy * 2;
						x = from->x;
						y = from->y;
						while (1)
						{
							mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
							x = x - 1;
							if (x == to->x)
								break ;
							e = e + dy;
							if (e >= 0)
							{
								y = y + 1;
								e = e + dx;
							}
						}
					}
					else
					{
						e = dy;
						dy = e * 2;
						dx = dx * 2;
						x = from->x;
						y = from->y;
						while (1)
						{
							mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
							y = y + 1;
							if (y == to->y)
								break ;
							e = e + dx;
							if (e <= 0)
							{
								x = x - 1;
								e = e + dy;
							}
						}
					}
				}
				else
				{
					if (dx <= dy)
					{
						e = dx;
						dx = e * 2;
						dy = dy * 2;
						x = from->x;
						y = from->y;
						while (1)
						{
							mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
							x = x - 1;
							if (x == to->x)
								break ;
							e = e - dy;
							if (e >= 0)
							{
								y = y - 1;
								e = e + dx;
							}
						}
					}
					else
					{
						e = dy;
						dy = e * 2;
						dx = dx * 2;
						x = from->x;
						y = from->y;
						while (1)
						{
							mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
							y = y - 1;
							if (y == to->y)
								break ;
							e = e - dx;
							if (e >= 0)
							{
								x = x - 1;
								e = e + dy;
							}
						}
					}
				}
			}
			else
			{
				x = from->x;
				y = from->y;
				while (x != to->x)
				{
					mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
					x = x - 1;
				}
			}
		}
	}
	else
	{
		if ((dy = to->y - from->y))
		{
			if (dy > 0)
			{
				x = from->x;
				y = from->y;
				while (y != to->y)
				{
					mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
					y = y + 1;
				}
			}
			else
			{
				x = from->x;
				y = from->y;
				while (y != to->y)
				{
					mlx_pixel_put(mlx->sess, mlx->win, x, y, mlx->col);
					y = y - 1;
				}
			}
		}
	}
}
*/

void	draw_square(t_mlx_sess *mlx_sess, t_vector2 *from, t_vector2 *to)
{
	int		i;
	int		j;
	//int		c;

	//c = 0x009933bb;
	i = from->x;
	j = from->y;
	while (i < to->x)
	{
		while (j < to->y)
		{
			mlx_pixel_put(mlx_sess->sess, mlx_sess->win, i, j, mlx_sess->col);
			j++;
		}
		j = from->y;
		i++;
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
