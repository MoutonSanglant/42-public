#include "fdf.h"

int		keypress(int key, void *p)
{
	t_mlx_sess	*sess;

	sess = (t_mlx_sess *)p;
#ifdef LINUX
	if (key == 65362)
	{
		ft_putchar('@');
		t_vector3 v;
		v.x = 10;
		v.y = 0;
		v.z = 0;
		sess->view = translate_matrix4(sess->view, v);
		//sess->view = scale_matrix4(sess->view, v);
		ft_putnbr((int)(*sess->view)[0][3]);
	}
	else if (key == 65364)
	{
		t_vector3 v;
		v.x = 0;
		v.y = 0;
		v.z = -1;
		sess->view = translate_matrix4(sess->view, v);
	}
	if (key == 65307)
#else
	if (key == 53)
#endif
	{
		mlx_destroy_window(sess->sess, sess->win);
		ft_memdel((void **)&sess);
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
	//if (T == 0)
	{
		mlx_clear_window(sess->sess, sess->win);
		gettimeofday(&tval_last, NULL);
		// TODO
		// Actually, redraw hover the image
		// on every tick, should be changed
		// so a draw call is invoked only
		// if an event occured
		draw_3dgrid(sess);
		mlx_put_image_to_window(sess->sess, sess->win, sess->img->img, 0, 0);
		//mlx_clear_window(sess->sess, sess->win);
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

#ifdef DEBUG
static void	post(t_image *image)
{
	output_image_info(image);
}
#else
static void	post(t_image *image)
{
	(void) image;
}
#endif

int		main(int argc, char **argv)
{
	t_mlx_sess	*param;
	t_vector3	*grid;
	t_image		image;
	int			local_endian;
	int			a;
	int			x;
	int			y;
	t_matrix4	*view;
	t_matrix4	*projection;

	view = (t_matrix4 *)malloc(sizeof(t_matrix4));
	view = identity_matrix4(view);
	identity_matrix4(view);
	projection = (t_matrix4 *)malloc(sizeof(t_matrix4));
	projection = identity_matrix4(projection);

	if (argc < 1)
		return (1);
	if (argc > 2)
	{
		x = ft_atoi(argv[1]);
		y = ft_atoi(argv[2]);
	}
	else
	{
		x = 500;
		y = 500;
	}

	param = (t_mlx_sess *)ft_memalloc(sizeof(t_mlx_sess));
	if (!(param->sess = mlx_init()))
	{
		ft_memdel((void **)&param);
		return (1);
	}
	param->width = x;
	param->height = y;
	if (!(param->win = mlx_new_window(param->sess, param->width, param->height, "test_mlx")))
	{
		ft_memdel((void **)&param);
		return (1);
	}
	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1; // big-endian
	else
		local_endian = 0; // little-endian
	(void) local_endian;
	image.img = mlx_new_image(param->sess, param->width * 2, param->height * 2);
	image.data = mlx_get_data_addr(image.img, &image.bpp, &image.sl, &image.endian);
	post(&image);
	param->img = &image;
	grid = (t_vector3 *)ft_memalloc(sizeof(t_vector3) * 10 * 10);
	init_grid(grid);
	param->grid = grid;
	param->view = view;
	param->projection = projection;
	param->col = 0x00ffffff;

	mlx_key_hook(param->win, &keypress, (void *)param);
	mlx_expose_hook(param->win, &expose, (void *)param);
	mlx_loop_hook(param->sess, &draw_loop, (void *)param);
	mlx_loop(param->sess);

	return (0);
}
