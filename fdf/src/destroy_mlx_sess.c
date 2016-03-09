/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mlx_sess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:09:25 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/09 12:19:47 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	destroy_mlx_sess(t_mlx_sess *sess)
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
	ft_memdel((void **)&sess->img);
	ft_memdel((void **)&sess->sess);
	ft_memdel((void **)&sess);
}
