#include "fdf.h"

void	rotate_around_center(t_mlx_sess *sess, int dir)
{
	t_mat4x4	m_iworld;
	t_mat4x4	m_rot;

	inverse_matrix4(sess->world, &m_iworld);
	identity_matrix4(&m_rot);
	rotation_z_matrix4(&m_rot, RAD(3 * dir));
	matrix4_product(&m_iworld, &m_rot);
	inverse_matrix4(&m_iworld, sess->world);
}

int		keydown(int key, void *p)
{
	t_mlx_sess	*sess;
	t_mat4x4	m_loc;
	t_mat4x4	m_rot;
	t_vec3f		loc;

	sess = (t_mlx_sess *)p;
	sess->need_update = 1;
	loc.x = 0;
	loc.y = 0;
	loc.z = 0;
	identity_matrix4(&m_loc);
	identity_matrix4(&m_rot);


	ft_putchar('\n');
	ft_putnbr(key);


	if (key == KEY_O)
		set_orthographic_camera(sess);
	else if (key == KEY_P)
		set_perspective_camera(sess);
	else if (key == KEY_Q)
		rotation_y_matrix4(&m_rot, RAD(3));
	else if (key == KEY_E)
		rotation_y_matrix4(&m_rot, RAD(-3));
	else if (key == KEY_A)
		rotate_around_center(sess, -1);
	else if (key == KEY_D)
		rotate_around_center(sess, 1);
	else if (key == KEY_W)
		rotation_x_matrix4(&m_rot, RAD(3));
	else if (key == KEY_S)
		rotation_x_matrix4(&m_rot, RAD(-3));
	else if (key == KEY_NUMPAD_MORE)
		loc.y = -1;
	else if (key == KEY_NUMPAD_LESS)
		loc.y = 1;
	else if (key == KEY_LEFT)
		loc.x = -1;
	else if (key == KEY_RIGHT)
		loc.x = 1;
	else if (key == KEY_UP)
		loc.z = -1;
	else if (key == KEY_DOWN)
		loc.z = 1;
	else if (key == KEY_PAGE_UP)
		change_grid_z_value(sess->grid, 1.1f);
	else if (key == KEY_PAGE_DOWN)
		change_grid_z_value(sess->grid, 0.9f);
	translation_matrix4(&m_loc, loc);
	matrix4_product(sess->world, &m_loc);
	matrix4_product(sess->world, &m_rot);
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
	sess->need_update = 1;
	return (0);
}

#ifdef DEBUG
static void	post_loading(t_image *image)
{
	output_image_info(image);
	(void) image;
}
#else
static void	post_loading(t_image *image)
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

	char txt[] = "hello";
	char dst[32];

	for (int j = 0; j < 12; ++j) {
		for (size_t i = 0; i < sizeof(txt); ++i) {
			dst[i + 6] = txt[i];
		}
		ft_memmove(dst + j, dst + 6, sizeof(txt));
		if (ft_memcmp(dst + j, txt, sizeof(txt) != 0))
				ft_putstr("sniff\n");
	}
	ft_putstr("Youpi!\n");

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
	param->img = &image;
	if (argc > 3)
		param->img->filename = argv[3];
	else
		param->img->filename = NULL;
	post_loading(&image);
	param->need_update = 1;

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
	{
		init_grid_from_vertmap(param->grid, vertmap, vx, vy);
		identity_matrix4(&param->m_model);

		t_mat4x4	trans;
		t_vec3f		loc;
		identity_matrix4(&trans);
		/*
		** Put model at the center of the scene
		*/
		loc.x = -param->grid->width * .5f;
		loc.y = -param->grid->height * .5f;
		loc.z = 0;
		translation_matrix4(&trans, loc);
		matrix4_product(&param->m_model, &trans);
	}
	else
	{
		ft_putendl("no input file !");
		init_grid(param->grid, 10, 10);
		identity_matrix4(&param->m_model);
	}
	param->col = 0x00ffffff;

	/*
	**	CUBE
	*/
	param->cube = (t_tri *)ft_memalloc(sizeof(t_tri) * 12);
	cube(param->cube);

	t_mat4x4	tmp;

	/*
	**	WORLD Matrix
	*/
	param->world = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4));

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
	rotation_x_matrix4(&tmp, RAD(90));
	matrix4_product(param->view, &tmp);
	inverse_matrix4(param->view, param->worldToCamera);

	// Move the world so it looks in a good direction

	/*
	**	PROJECTION Matrix
	*/
	param->projection = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4));

	// Aspect of the window

	// Camera
	param->camera.aspect = (float)param->width / (float)param->height;
	param->camera.near = .1f;
	param->camera.far = 100;
	param->camera.angle_of_view = 90.f;
	param->camera.right = .1f * param->camera.aspect;
	param->camera.top = .1f;
	param->camera.left = -param->camera.right;
	param->camera.bottom = -param->camera.top;
	param->camera.far = 100.f;
// Use an horizontal FOV
	set_perspective_camera(param);

	/*
	**	ORTHOGRAPHIC
	*/
	// Canvas Height
	param->canvasH = 2 * tan(90.f * .5f) * param->camera.near;
	param->canvasW = param->canvasH * param->camera.aspect;
	param->canvasT = param->canvasH * .5f;
	param->canvasB = -param->canvasT;

	param->canvasR = param->canvasT * .5f;
	param->canvasL = -param->canvasR;

	/*
	**	DRAWING Settings
	*/
	param->line_width = .06f;
	param->lines_color = 0x00000000;
	param->bg_color = 0x00046000;
	//param->faces_color = param->bg_color;
	//param->faces_color = 0x00ff0000;
	// invert
	//param->faces_color = param->lines_color;
	//param->lines_color = param->bg_color;

	printf("height: %i / width: %i\naspect: %f\nH: %f / W: %f\nT: %f\nB: %f\nL: %f\nR: %f\n", param->height, param->width, param->camera.aspect, param->canvasH, param->canvasW, param->canvasT, param->canvasB, param->canvasL, param->canvasR);

	// Start MLX session
	mlx_hook(param->win, KeyPress, KeyPressMask, &keydown, (void *)param);
	mlx_key_hook(param->win, &keypress, (void *)param);
	mlx_expose_hook(param->win, &expose, (void *)param);
	mlx_loop_hook(param->sess, &draw_loop, (void *)param);
	mlx_loop(param->sess);
	return (0);
}
