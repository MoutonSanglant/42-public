#include <stdio.h>
#include <stdlib.h>
#include <includes/libft.h>
#include "mlx.h"
//#include "mlx_int.h"

typedef struct	s_mlx_sess
{
	void	*mlx_sess;
	void	*mlx_win;
}				t_mlx_sess;

int		keypress(int key, void *p)
{
	(void)	p;

	/* debug key
	** ft_putnbr(key);
	** ft_putchar('\n');
	*/
	if (key == 0x7)
	{
		free(p);
		exit(0);
	}
	return (0);
}

int		loop(void *p)
{
	static int	x = 0;
	static int	y = 0;
	static int	r = 0;
	static int	g = 0;
	static int	b = 0;
	t_mlx_sess	*mlx_sess;
	int			c;

	c = r | g | b;
	mlx_sess = (t_mlx_sess *)p;
	mlx_pixel_put(mlx_sess->mlx_sess, mlx_sess->mlx_win, x, y, c);
	mlx_pixel_put(mlx_sess->mlx_sess, mlx_sess->mlx_win, x + 1, y, c);
	mlx_pixel_put(mlx_sess->mlx_sess, mlx_sess->mlx_win, x, y + 1, c);
	mlx_pixel_put(mlx_sess->mlx_sess, mlx_sess->mlx_win, x + 1, y + 1, c);
	x += 2;
	if (x >= 199)
	{
		y += 2;
		x = 0;
		if (y >= 199)
			y = 0;
	}
	r += 0x000001;
	g += 0x000200;
	b += 0x080000;
	return (0);
}

int		main()
{
	void		*mlx_sess;
	void		*mlx_win;
	t_mlx_sess	*param;

	mlx_sess = mlx_init();
	mlx_win = mlx_new_window(mlx_sess, 200, 200, "test");
	param = (t_mlx_sess *)malloc(sizeof(t_mlx_sess));
	param->mlx_sess = mlx_sess;

	if (mlx_win)
	{
		param->mlx_win = mlx_win;
		mlx_key_hook(mlx_win, &keypress, (void *)param);
		mlx_loop_hook(mlx_sess, &loop, (void *)param);
		mlx_loop(mlx_sess);
		free(param);
		mlx_destroy_window(mlx_sess, mlx_win);
	}

	return (0);
}
