#include "fdf.h"

int		keypress(int key, void *p)
{
	t_mlx_sess	*sess;
	t_matrix4	trans;

	identity_matrix4(&trans);
	sess = (t_mlx_sess *)p;
#ifdef LINUX
	if (key == 97)
	{
		rotationX_matrix4(&trans, RAD(3));
		multiply_matrix4(sess->view, &trans);
	}
	else if (key == 101)
	{
		rotationX_matrix4(&trans, RAD(-3));
		multiply_matrix4(sess->view, &trans);
	}
	if (key == 113)
	{
		rotationY_matrix4(&trans, RAD(3));
		multiply_matrix4(sess->view, &trans);
	}
	else if (key == 100)
	{
		rotationY_matrix4(&trans, RAD(-3));
		multiply_matrix4(sess->view, &trans);
	}
	if (key == 122)
	{
		rotationZ_matrix4(&trans, RAD(3));
		multiply_matrix4(sess->view, &trans);
	}
	else if (key == 115)
	{
		rotationZ_matrix4(&trans, RAD(-3));
		multiply_matrix4(sess->view, &trans);
	}

	if (key == 65361)
	{
		t_vector3 v;
		v.x = -10;
		v.y = 0;
		v.z = 0;
		translation_matrix4(&trans, v);
		multiply_matrix4(sess->view, &trans);
		//sess->view = translate_matrix4(sess->view, v);
	}
	else if (key == 65362)
	{
		ft_putchar('@');
		t_vector3 v;
		v.x = 0;
		v.y = -10;
		v.z = 0;
		translation_matrix4(&trans, v);
		multiply_matrix4(sess->view, &trans);
		//sess->view = translate_matrix4(sess->view, v);
		//sess->view = scale_matrix4(sess->view, v);
		ft_putnbr((int)(*sess->view)[3]);
	}
	if (key == 65363)
	{
		t_vector3 v;
		v.x = 10;
		v.y = 0;
		v.z = 0;
		translation_matrix4(&trans, v);
		multiply_matrix4(sess->view, &trans);
		//sess->view = translate_matrix4(sess->view, v);
	}
	else if (key == 65364)
	{
		t_vector3 v;
		v.x = 0;
		v.y = 10;
		v.z = 0;
		translation_matrix4(&trans, v);
		multiply_matrix4(sess->view, &trans);
		//sess->view = translate_matrix4(sess->view, v);
	}
	if (key == 65307)
#else
	if (key == 53)
#endif
	{
		//mlx_destroy_window(sess->sess, sess->win);
		//ft_memdel((void **)&sess);

		mlx_destroy_image(sess->sess, sess->img->img);
		mlx_destroy_window(sess->sess, sess->win);
		ft_memdel((void **)&sess->view);
		ft_memdel((void **)&sess->projection);
		ft_memdel((void **)&sess->grid);
		ft_memdel((void **)&sess->sess);
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
		//mlx_clear_window(sess->sess, sess->win);
		gettimeofday(&tval_last, NULL);
		// TODO
		// Actually, redraw hover the image
		// on every tick, should be changed
		// so a draw call is invoked only
		// if an event occured
		//clear_canvas(sess, 0xffffff);
		clear_canvas(sess, 0x00000000);
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
	//clear_canvas(sess, 0x00ffffff);
	(void)sess;
	//mlx_clear_window(sess->sess, sess->win);
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
	t_image		image;
	int			local_endian;
	int			a;
	int			x;
	int			y;

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
	if (local_endian == 1)
		return (1);

	/*
	**	IMAGE
	*/
	image.img = mlx_new_image(param->sess, param->width * 2, param->height * 2);
	image.data = mlx_get_data_addr(image.img, &image.bpp, &image.sl, &image.endian);
	post(&image);
	param->img = &image;
	clear_canvas(param->sess, 0xffffff);

	/*
	**	GRID
	*/
	param->grid = (t_vector3 *)ft_memalloc(sizeof(t_vector3) * 10 * 10);
	init_grid(param->grid);
	param->col = 0x00ffffff;

	t_matrix4	tmp;
	t_vector3 v;

	param->view = (t_matrix4 *)ft_memalloc(sizeof(t_matrix4));
	identity_matrix4(param->view);
	v.x = 300;
	v.y = 500;
	v.z = 10;
	rotationY_matrix4(&tmp, RAD(-30));
	//multiply_matrix4(param->view, &tmp);
	rotationX_matrix4(&tmp, RAD(160));
	//multiply_matrix4(param->view, &tmp);
	//rotationZ_matrix4(&tmp, RAD(45));
	translation_matrix4(&tmp, v);
	//multiply_matrix4(param->view, &tmp);

	param->projection = (t_matrix4 *)ft_memalloc(sizeof(t_matrix4));

	// Orthographic
	t_vector2 size;
	size.x = 1;
	size.y = 1;
	orthographic_projection_matrix4(param->projection, size, 5, 1000);

	// Perspective
	t_vector2 FOV;
	FOV.x = 90;
	FOV.y = 90;
	perspective_projection_matrix4(param->projection, FOV, 5, 1000);


	mlx_key_hook(param->win, &keypress, (void *)param);
	//mlx_expose_hook(param->win, &expose, (void *)param);
	mlx_loop_hook(param->sess, &draw_loop, (void *)param);
	mlx_loop(param->sess);
	return (0);
}
