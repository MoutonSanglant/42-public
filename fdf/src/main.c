#include "fdf.h"

int		keydown(int key, void *p)
{
	t_mlx_sess	*sess;
	t_mat4x4	trans;

	identity_matrix4(&trans);
	sess = (t_mlx_sess *)p;

	sess->need_update = 1;

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
		t_vec3f v;
		v.x = 0;
		v.y = 0;
		v.z = 1;
		translation_matrix4(&trans, v);
	}
	else if (key == KEY_NUMPAD_LESS)
	{
		t_vec3f v;
		v.x = 0;
		v.y = 0;
		v.z = -1;
		translation_matrix4(&trans, v);
	}
	else if (key == KEY_LEFT)
	{
		t_vec3f v;
		v.x = -1;
		v.y = 0;
		v.z = 0;
		translation_matrix4(&trans, v);
	}
	else if (key == KEY_UP)
	{
		t_vec3f v;
		v.x = 0;
		v.y = -1;
		v.z = 0;
		translation_matrix4(&trans, v);
	}
	else if (key == KEY_RIGHT)
	{
		t_vec3f v;
		v.x = 1;
		v.y = 0;
		v.z = 0;
		translation_matrix4(&trans, v);
	}
	else if (key == KEY_DOWN)
	{
		t_vec3f v;
		v.x = 0;
		v.y = 1;
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

#ifdef DEBUG
static void	draw_gui(t_mlx_sess *p)
{
	draw_debug_gui(p);
	(void) p;
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
	if (tval_tic.tv_usec > FPS && sess->need_update)
	{
		gettimeofday(&tval_last, NULL);
		//clear_canvas(sess, 0xffffff);
		clear_canvas(sess, sess->bg_color);
		draw_3dgrid(sess);
		mlx_put_image_to_window(sess->sess, sess->win, sess->img->img, 0, 0);
		draw_gui(sess);
		sess->need_update = 0;
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
	t_vert		**vertmap;

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

	int vx, vy;

	vx = 0;
	vy = 0;
	vertmap = NULL;
	if (argc > 3)
		vertmap = get_vertmap_from_file(argv[3], &vx, &vy);
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
	param->need_update = 1;
	//clear_canvas(param->sess, 0xffffff);

	/*
	**	Z-BUFFER
	*/

#ifdef BONUS
	param->zbuffer = (float *)ft_memalloc(sizeof(float) * x * y);
	//clear_zbuffer(param->zbuffer, x, y);
#endif

	/*
	**	GRID
	*/
	param->grid = (t_grid *)ft_memalloc(sizeof(t_grid));
	if (vertmap)
		init_grid_from_vertmap(param->grid, vertmap, vx, vy);
	else
	{
		ft_putendl("no input file !");
		//init_grid(param->grid, 10, 10);
		init_grid(param->grid, 1, 1);
	}
	param->col = 0x00ffffff;

	/*
	**	CUBE
	*/
	param->cube = (t_tri *)ft_memalloc(sizeof(t_tri) * 12);
	cube(param->cube);

	t_mat4x4	tmp;
	t_vec3f v;

	/*
	**	WORLD Matrix
	*/
	param->world = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4));
	identity_matrix4(param->world);

	/*
	**	VIEW MAtrix
	*/
	param->view = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4));
	identity_matrix4(param->view);

	/*
	**	CAMERA Matrix (WorldToCamera)
	*/
	param->worldToCamera = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4));
	// Camera needs to look down (along the negative 'Z-axis')
	rotationX_matrix4(&tmp, RAD(90));
	matrix4_product(param->view, &tmp);
	inverse_matrix4(param->view, param->worldToCamera);

	// Move the world so it looks in a good direction
	rotationZ_matrix4(&tmp, RAD(180));
	matrix4_product(param->world, &tmp);
	v.x = 18;
	v.y = 20;
	v.z = -6;
	translation_matrix4(&tmp, v);
	matrix4_product(param->world, &tmp);
	rotationX_matrix4(&tmp, RAD(-10));
	matrix4_product(param->world, &tmp);
	rotationZ_matrix4(&tmp, RAD(-25));
	matrix4_product(param->world, &tmp);

	/*
	**	PROJECTION Matrix
	*/
	param->projection = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4));

	// Aspect of the window
	param->aspect = (float)param->width / (float)param->height;

	// Perspective Camera
	param->near = .1f;
	param->far = 100;
	// Use an horizontal FOV
	perspective_projection_matrix4(param->projection, 90.f, param->aspect, param->near, param->far);

	/*
	**	ORTHOGRAPHIC
	*/
	/*float t, b, l, r;
	r = param->width * param->aspect;
	t = param->width;
	r = -.1f * param->aspect;
	t = -.1f;
	l = -r;
	b = -t;
	orthographic_projection_matrix4(param->projection, t, b, l, r, 1.f, 100);*/
	// Canvas Height
	param->canvasH = 2 * tan(90.f * .5f) * param->near;
	param->canvasW = param->canvasH * param->aspect;
	param->canvasT = param->canvasH * .5f;
	param->canvasB = -param->canvasT;

	param->canvasR = param->canvasT * .5f;
	param->canvasL = -param->canvasR;

	/*
	**	DRAWING Settings
	*/
	param->line_width = .03f;
	param->lines_color = 0x00000000;
	param->bg_color = 0x00046000;
	param->faces_color = param->bg_color;
	// invert
	param->faces_color = param->lines_color;
	param->lines_color = param->bg_color;

	printf("height: %i / width: %i\naspect: %f\nH: %f / W: %f\nT: %f\nB: %f\nL: %f\nR: %f\n", param->height, param->width, param->aspect, param->canvasH, param->canvasW, param->canvasT, param->canvasB, param->canvasL, param->canvasR);

	// Start MLX session
	mlx_hook(param->win, KeyPress, KeyPressMask, &keydown, (void *)param);
	mlx_key_hook(param->win, &keypress, (void *)param);
	//mlx_expose_hook(param->win, &expose, (void *)param);
	mlx_loop_hook(param->sess, &draw_loop, (void *)param);
	mlx_loop(param->sess);
	return (0);
}
