#include "fdf.h"

void	draw_line(t_mlx_sess *mlx_sess, t_vector3 from, t_vector3 to)
{
	int		i;
	int		j;
	int		c;

	c = 0x009933bb;
	i = from.x;
	j = from.y;
	while (i < to.x)
	{
		while (j < to.y)
		{
			mlx_pixel_put(mlx_sess->sess, mlx_sess->win, i, j, c);
			j++;
		}
		j = from.y;
		i++;
	}
}

void	draw_square(t_mlx_sess *mlx_sess, t_vector3 from, t_vector3 to)
{
	int		i;
	int		j;
	int		c;

	c = 0x009933bb;
	i = from.x;
	j = from.y;
	while (i < to.x)
	{
		while (j < to.y)
		{
			mlx_pixel_put(mlx_sess->sess, mlx_sess->win, i, j, c);
			j++;
		}
		j = from.y;
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

void	draw_picture(t_mlx_sess *mlx_sess)
{
	static void		*img = 0;
	static int		x = 0;
	static int		y = 0;

	if (!img)
	{
		//img = mlx_new_image(mlx_sess->sess, x, y);
		img = mlx_xpm_file_to_image(mlx_sess->sess, "./img.xpm", &x, &y);
	}
	mlx_put_image_to_window(mlx_sess->sess, mlx_sess->win, img, 0, 0);
	mlx_string_put(mlx_sess->sess, mlx_sess->win, 0, 0, 0x00ff0000, "Hello");
}
