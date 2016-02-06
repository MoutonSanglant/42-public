/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:02:46 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/06 07:49:05 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		init_buffers(t_mlx_sess *sess, char *filename)
{
	sess->img = (t_image *)ft_memalloc(sizeof(t_image));
	if (!sess->img)
		alloc_error("sess->img", sizeof(t_image));
	sess->img->img = mlx_new_image(sess->sess, sess->width, sess->height);
	if (!sess->img->img)
		alloc_error("sess->img->img", sizeof(int) * sess->width * sess->height);
	sess->img->data = mlx_get_data_addr(sess->img->img, &sess->img->bpp,
										&sess->img->sl, &sess->img->endian);
	sess->img->filename = filename;
	sess->zbuffer = (float *)ft_memalloc(sizeof(float)
											* sess->width * sess->height);
	if (!sess->zbuffer)
		alloc_error("sess->zbuffer", sizeof(float)
										* sess->width * sess->height);
}

static void		init_vertex_grid(t_mlx_sess *sess, t_vert **vertmap,
									int x, int y)
{
	t_mat4x4	trans;
	t_vec3f		loc;

	if (!(sess->grid = (t_grid *)ft_memalloc(sizeof(t_grid))))
		alloc_error("sess->grid", sizeof(t_grid));
	if (vertmap)
		init_grid_from_vertmap(sess->grid, vertmap, x, y);
	else
	{
		ft_putendl_fd("No input file, making a 10x10 flat grid.", 1);
		init_grid(sess->grid, 10, 10);
	}
	identity_matrix4(&sess->m_model);
	identity_matrix4(&trans);
	loc.x = -sess->grid->width * .5f;
	loc.y = -sess->grid->height * .5f;
	loc.z = 0;
	translation_matrix4(&trans, loc);
	matrix4_product(&trans, &sess->m_model);
	sess->options.distance = (int)fmaxf(sess->grid->width, sess->grid->height);
}

static void		get_size(int argc, char **argv, t_vec2 *screen_size)
{
	screen_size->x = DEFAULT_WIDTH;
	screen_size->y = DEFAULT_HEIGHT;
	if (argc > 2)
	{
		screen_size->x = ft_atoi(argv[1]);
		screen_size->y = ft_atoi(argv[2]);
		if (screen_size->x < MIN_WIDTH || screen_size->x > MAX_WIDTH)
		{
			ft_putstr_fd("Width must be a value between ", 2);
			ft_putnbr_fd(MIN_WIDTH, 2);
			ft_putstr_fd(" and ", 2);
			ft_putnbr_fd(MAX_WIDTH, 2);
			ft_putchar_fd('\n', 2);
			exit(1);
		}
		if (screen_size->y < MIN_HEIGHT || screen_size->y > MAX_HEIGHT)
		{
			ft_putstr_fd("Height must be a value between ", 2);
			ft_putnbr_fd(MIN_HEIGHT, 2);
			ft_putstr_fd(" and ", 2);
			ft_putnbr_fd(MAX_HEIGHT, 2);
			ft_putchar_fd('\n', 2);
			exit(1);
		}
	}
}

static void		arguments_count_error(void)
{
	ft_putendl_fd(USAGE_MSG, 2);
	exit(1);
}

int				main(int argc, char **argv)
{
	t_vert		**vertmap;
	char		*filepath;
	t_mlx_sess	*sess;
	t_vec2		vertmap_size;
	t_vec2		screen_size;

	filepath = NULL;
	vertmap = NULL;
	vertmap_size.x = 0;
	vertmap_size.y = 0;
	if (argc < 1 || argc > 4)
		arguments_count_error();
	get_size(argc, argv, &screen_size);
	if (argc > 3)
	{
		filepath = argv[3];
		vertmap = get_vertmap_from_file(argv[3],
										&vertmap_size.x, &vertmap_size.y);
	}
	sess = init_mlx_sess(screen_size.x, screen_size.y);
	init_buffers(sess, filepath);
	init_vertex_grid(sess, vertmap, vertmap_size.x, vertmap_size.y);
	start_mlx_sess(sess);
	return (0);
}
