#include "fdf.h"

int		keydown(int key, void *p)
{
	t_mlx_sess	*sess;
	t_matrix4	trans;

	identity_matrix4(&trans);
	sess = (t_mlx_sess *)p;

	if (key == KEY_Q)
		rotationY_matrix4(&trans, RAD(3));
	else if (key == KEY_E)
		rotationY_matrix4(&trans, RAD(-3));
	else if (key == KEY_A)
		rotationZ_matrix4(&trans, RAD(-3));
	else if (key == KEY_D)
		rotationZ_matrix4(&trans, RAD(3));
	else if (key == KEY_W)
		rotationX_matrix4(&trans, RAD(3));
	else if (key == KEY_S)
		rotationX_matrix4(&trans, RAD(-3));
	else if (key == KEY_NUMPAD_MORE)
	{
		t_vector3 v;
		v.x = 0;
		v.y = 0;
		v.z = 40;
		translation_matrix4(&trans, v);
	}
	else if (key == KEY_NUMPAD_LESS)
	{
		t_vector3 v;
		v.x = 0;
		v.y = 0;
		v.z = -40;
		translation_matrix4(&trans, v);
	}
	else if (key == KEY_LEFT)
	{
		t_vector3 v;
		v.x = -40;
		v.y = 0;
		v.z = 0;
		translation_matrix4(&trans, v);
	}
	else if (key == KEY_UP)
	{
		t_vector3 v;
		v.x = 0;
		v.y = -40;
		v.z = 0;
		translation_matrix4(&trans, v);
	}
	else if (key == KEY_RIGHT)
	{
		t_vector3 v;
		v.x = 40;
		v.y = 0;
		v.z = 0;
		translation_matrix4(&trans, v);
	}
	else if (key == KEY_DOWN)
	{
		t_vector3 v;
		v.x = 0;
		v.y = 40;
		v.z = 0;
		translation_matrix4(&trans, v);
	}
	matrix4_product(sess->world, &trans);
	return (0);
}

int		keypress(int key, void *p)
{
	t_mlx_sess	*sess;

	sess = (t_mlx_sess *)p;
#ifdef LINUX
	if (key == 65307)
#else
	if (key == 53)
#endif
	{
		//mlx_destroy_window(sess->sess, sess->win);
		//ft_memdel((void **)&sess);

		mlx_destroy_image(sess->sess, sess->img->img);
		mlx_destroy_window(sess->sess, sess->win);
		ft_memdel((void **)&sess->zbuffer);
		ft_memdel((void **)&sess->world);
		ft_memdel((void **)&sess->view);
		ft_memdel((void **)&sess->worldToCamera);
		ft_memdel((void **)&sess->projection);
		ft_memdel((void **)&sess->grid->triangles);
		ft_memdel((void **)&sess->grid);
		ft_memdel((void **)&sess->cube);
		ft_memdel((void **)&sess->sess);
		ft_memdel((void **)&sess);
		exit(0);
	}
	return (0);
}

#include <stdio.h>
#ifdef DEBUG
static void	draw_gui(t_mlx_sess *p)
{
	static char *camera[3];

	if (!camera[0])
	{
		/*
		** MEMORY IS DEFINETLY LOST !!
		*/
		camera[0] = (char *)ft_memalloc(sizeof(char) * 20);
		camera[0] = ft_strcpy(camera[0], "  x: ");
		camera[1] = (char *)ft_memalloc(sizeof(char) * 20);
		camera[1] = ft_strcpy(camera[1], "  y: ");
		camera[2] = (char *)ft_memalloc(sizeof(char) * 20);
		camera[2] = ft_strcpy(camera[2], "  z: ");
	}

	mlx_string_put(p->sess, p->win, 5, 15, 0x00ffffff, "DEBUG CONSOLE");
	mlx_string_put(p->sess, p->win, 5, 30, 0x00ffffff, "Camera");
	ft_strncpy(&camera[0][5], ft_itoa((int)(*p->world)[3]), 3);
	camera[0][8] = '\0';
	mlx_string_put(p->sess, p->win, 5, 45, 0x00ffffff, camera[0]);
	ft_strncpy(&camera[1][5], ft_itoa((int)(*p->world)[7]), 3);
	camera[1][8] = '\0';
	mlx_string_put(p->sess, p->win, 5, 60, 0x00ffffff, camera[1]);
	ft_strncpy(&camera[2][5], ft_itoa((int)(*p->world)[11]), 3);
	camera[2][8] = '\0';
	mlx_string_put(p->sess, p->win, 5, 75, 0x00ffffff, camera[2]);
}
#else
static void	draw_gui(t_mlx_sess *p)
{
	(void) p;
}
#endif

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
		draw_gui(sess);
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

#include <stdio.h>

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
		x = 800;
		y = 600;
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
	**	FRAME_BUFFER
	*/
	image.img = mlx_new_image(param->sess, param->width, param->height);
	image.data = mlx_get_data_addr(image.img, &image.bpp, &image.sl, &image.endian);
	post(&image);
	param->img = &image;
	//clear_canvas(param->sess, 0xffffff);

	/*
	**	Z-BUFFER
	*/
	param->zbuffer = (float *)ft_memalloc(sizeof(float) * x * y);

	/*
	**	GRID
	*/
	param->grid = (t_grid *)ft_memalloc(sizeof(t_grid));
	init_grid(param->grid, 10, 10);
	param->col = 0x00ffffff;

	/*
	**	CUBE
	*/
	param->cube = (t_triangle *)ft_memalloc(sizeof(t_triangle) * 12);
	cube(param->cube);

	t_matrix4	tmp;
	t_vector3 v;

	// World
	param->world = (t_matrix4 *)ft_memalloc(sizeof(t_matrix4));
	identity_matrix4(param->world);

	param->view = (t_matrix4 *)ft_memalloc(sizeof(t_matrix4));
	identity_matrix4(param->view);
	// Camera needs to look down (along the negative 'Z-axis')
	rotationX_matrix4(&tmp, RAD(90));
	matrix4_product(param->view, &tmp);
	param->worldToCamera = (t_matrix4 *)ft_memalloc(sizeof(t_matrix4));
	inverse_matrix4(param->view, param->worldToCamera);
	v.x = 0;
	v.y = 0;
	v.z = 50;
	translation_matrix4(&tmp, v);
	//matrix4_product(param->view, &tmp);
	//(*param->view)[3] = 0;
	//(*param->view)[7] = 0;
	//(*param->view)[11] = 0;
	v.x = 0;
	v.y = 50;
	v.z = 0;
	rotationY_matrix4(&tmp, RAD(-30));
	//matrix4_product(param->view, &tmp);
	//matrix4_product(param->view, &tmp);
	//rotationZ_matrix4(&tmp, RAD(45));
	//matrix4_product(&tmp, &tmp2);
	//matrix4_product(param->view, &tmp);
	v.x = -200;
	v.y = 650;
	v.z = -300;
	translation_matrix4(&tmp, v);
	matrix4_product(param->world, &tmp);
	rotationX_matrix4(&tmp, RAD(-10));
	matrix4_product(param->world, &tmp);
	rotationZ_matrix4(&tmp, RAD(-10));
	matrix4_product(param->world, &tmp);

	param->projection = (t_matrix4 *)ft_memalloc(sizeof(t_matrix4));

	// Orthographic
	t_vector2 size;
	size.x = 1;
	size.y = 1;
	orthographic_projection_matrix4(param->projection, size, 5, 1000);

	// Perspective
	float FOV;
	FOV = 90.f; // just need horizontal FOV
	param->near = .1f;
	param->far = 1000;
	perspective_projection_matrix4(param->projection, FOV, x/y, param->near, param->far);

	//t_matrix4 camera = { 0.718762, 0.615033, -0.324214, 0, -0.393732, 0.744416, 0.539277, 0, 0.573024, -0.259959, 0.777216, 0, 0.526967, 1.254234, -2.53215, 1};
	//param->view = &camera;
	//param->canvasS = tan(FOV * .5f) * param->near;
	param->aspect = (float)param->width / (float)param->height;
	param->canvasH = 2 * tan(FOV * .5f) * param->near;
	param->canvasT = param->canvasH * .5f; // MAYBE a missing '* param->near' here
	param->canvasB = -param->canvasT;

	/* This solution needs x/y FOV
	** read 3D Viewing: the Pinhole Camera Chapter 4
	param->canvasW = 2 * tan(yFOV * .5f) * param->near;
	param->canvasR = param->canvasW * .5f; // MAYBE a missing '* param->near' here
	*/
	param->canvasW = param->canvasH * param->aspect;
	param->canvasR = param->canvasT * param->aspect; // MAYBE a missing '* param->near' here
	param->canvasL = -param->canvasR;

	printf("height: %i / width: %i\naspect: %f\nH: %f / W: %f\nT: %f\nB: %f\nL: %f\nR: %f\n", param->height, param->width, param->aspect, param->canvasH, param->canvasW, param->canvasT, param->canvasB, param->canvasL, param->canvasR);

	mlx_hook(param->win, KeyPress, KeyPressMask, &keydown, (void *)param);
	mlx_key_hook(param->win, &keypress, (void *)param);
	//mlx_expose_hook(param->win, &expose, (void *)param);
	mlx_loop_hook(param->sess, &draw_loop, (void *)param);
	mlx_loop(param->sess);
	return (0);
}
