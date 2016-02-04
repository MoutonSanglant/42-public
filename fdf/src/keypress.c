/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:14:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 14:15:05 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		keypress(int key, void *p)
{
	t_mlx_sess	*sess;

	sess = (t_mlx_sess *)p;
	if (key == KEY_ESCAPE)
	{
		mlx_destroy_image(sess->sess, sess->img->img);
		mlx_destroy_window(sess->sess, sess->win);
		ft_memdel((void **)&sess->zbuffer);
		ft_memdel((void **)&sess->world);
		ft_memdel((void **)&sess->view);
		ft_memdel((void **)&sess->world_to_camera);
		ft_memdel((void **)&sess->projection);
		ft_memdel((void **)&sess->grid->triangles);
		ft_memdel((void **)&sess->grid);
		ft_memdel((void **)&sess->sess);
		ft_memdel((void **)&sess);
		exit(0);
	}
	return (0);
}
