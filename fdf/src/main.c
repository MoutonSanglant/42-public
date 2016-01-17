#include "fdf.h"

int		keypress(int key, void *p)
{
	t_mlx_sess	*mlx_sess;

	mlx_sess = (t_mlx_sess *)p;
#ifdef LINUX
	if (key == 65307)
#else
	if (key == 53)
#endif
	{
		mlx_destroy_window(mlx_sess->sess, mlx_sess->win);
		free(mlx_sess);
		exit(0);
	}
	return (0);
}

#ifdef BONUS
int		draw_loop(void *p)
{
	static struct timeval	tval_last = {0,0};
	t_mlx_sess	*sess;
	struct timeval			tval_now;
	struct timeval			tval_tic;

	sess = (t_mlx_sess *)p;
	gettimeofday(&tval_now, NULL);
	timersub(&tval_now, &tval_last, &tval_tic);
	if (tval_tic.tv_usec > FPS)
	{
		mlx_clear_window(sess->sess, sess->win);
		gettimeofday(&tval_last, NULL);
		draw_3dgrid(sess);
		mlx_put_image_to_window(sess->sess, sess->win, sess->img->img, 0, 0);
	}
	return (0);
}
#else
int		draw_loop(void *p)
{
	(void) p;
	return (0);
}

#endif

int		expose(void *p)
{
	t_mlx_sess	*sess;

	sess = (t_mlx_sess *)p;
	mlx_clear_window(sess->sess, sess->win);
//	draw_3dgrid(sess);

	return (0);
}

int		main()
{
	t_mlx_sess	*param;

	param = (t_mlx_sess *)malloc(sizeof(t_mlx_sess));
	if (!(param->sess = mlx_init()))
	{
		free(param);
		return (1);
	}
	if (!(param->win = mlx_new_window(param->sess, 200, 200, "test_mlx")))
	{
		free(param);
		return (1);
	}
	int local_endian;
	int a;
	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1; // big-endian
	else
		local_endian = 0; // little-endian
	//param->img_data = mlx_get_data_addr(param->img, &bpp, &sl, &endian);
	t_image image;
//	image = (t_image *)malloc(sizeof(t_image));
	//image.img = mlx_xpm_file_to_image(param->sess, "./img.xpm", &x, &y);
	image.img = mlx_new_image(param->sess, 200, 200);
	image.data = mlx_get_data_addr(image.img, &image.bpp, &image.sl, &image.endian);
	
	param->img = &image;
	ft_putstr("Image at ");
	ft_putaddr(image.data);
	ft_putstr(", bpp: ");
	ft_putnbr(image.bpp);
	ft_putstr(", sl: ");
	ft_putnbr(image.sl);
	ft_putstr(", endian: ");
	ft_putnbr(image.endian);
	ft_putstr("(local: ");
	ft_putnbr(local_endian);
	ft_putendl(")");
//	just_a_test(param->sess, (unsigned char *)param->img_data, bpp, sl, 200, 200, endian);

	//mlx_put_image_to_window(param->sess, param->win, param->img, 0, 0);

	mlx_key_hook(param->win, &keypress, (void *)param);
	mlx_expose_hook(param->win, &expose, (void *)param);
	mlx_loop_hook(param->sess, &draw_loop, (void *)param);
	mlx_loop(param->sess);

	return (0);
}
