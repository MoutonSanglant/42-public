/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:02:46 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 16:30:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_buffers(t_mlx_sess *sess, char *filename)
{
	sess->img = (t_image *)malloc(sizeof(t_image));
	if (!sess->img)
		alloc_error("sess->img", sizeof(t_image));
	sess->img->img = mlx_new_image(sess->sess, sess->width, sess->height);
	if (!sess->img->img)
		alloc_error("sess->img->img", sizeof(int) * sess->width * sess->height);
	sess->img->data = mlx_get_data_addr(sess->img->img, &sess->img->bpp, &sess->img->sl, &sess->img->endian);
	sess->img->filename = filename;
	sess->zbuffer = (float *)ft_memalloc(sizeof(float) * sess->width * sess->height);
	if (!sess->zbuffer)
		alloc_error("sess->zbuffer", sizeof(float) * sess->width * sess->height);
}

static void	init_vertex_grid(t_mlx_sess *sess, t_vert **vertmap, int x, int y)
{
	t_mat4x4	trans;
	t_vec3f		loc;

	sess->grid = (t_grid *)ft_memalloc(sizeof(t_grid));
	if (!sess->zbuffer)
		alloc_error("sess->grid", sizeof(t_grid));
	if (vertmap)
		init_grid_from_vertmap(sess->grid, vertmap, x, y);
	else
	{
		ft_putendl("No input file, making a 10x10 flat grid.");
		init_grid(sess->grid, 10, 10);
	}
	identity_matrix4(&sess->m_model);
	identity_matrix4(&trans);
	loc.x = -sess->grid->width * .5f;
	loc.y = -sess->grid->height * .5f;
	loc.z = 0;
	translation_matrix4(&trans, loc);
	matrix4_product(&trans, &sess->m_model);
}

int		main(int argc, char **argv)
{
	t_vert		**vertmap;
	t_mlx_sess	*sess;
	int			a;
	int			x;
	int			y;
	char *filepath;
	int vx, vy;
	int			local_endian;

	filepath = NULL;

	x = 800;
	y = 600;
	if (argc < 1 || argc > 4)
	{
		ft_putendl(USAGE_MSG);
		return (1);
	}
	if (argc > 2)
	{
		x = ft_atoi(argv[1]);
		y = ft_atoi(argv[2]);
	}
	else
	{
	}

	vx = 0;
	vy = 0;
	vertmap = NULL;
	if (argc > 3)
		filepath = argv[3];

	if (filepath)
		vertmap = get_vertmap_from_file(argv[3], &vx, &vy);

	sess = init_mlx_sess(x, y);

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1; // big-endian
	else
		local_endian = 0; // little-endian
	if (local_endian == 1)
		return (1);

	init_buffers(sess, filepath);
	init_vertex_grid(sess, vertmap, vx, vy);

	
	/*
	**	DRAWING Settings
	*/
	// invert

//	printf("height: %i / width: %i\naspect: %f\nH: %f / W: %f\nT: %f\nB: %f\nL: %f\nR: %f\n", param->height, param->width, param->camera.aspect, param->canvasH, param->canvasW, param->canvasT, param->canvasB, param->canvasL, param->canvasR);
	


	start_mlx_sess(sess);
	return (0);
}
