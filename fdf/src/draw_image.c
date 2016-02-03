/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:54:03 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/03 16:54:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_image(t_mlx_sess *mlx_sess, void *img, int *x, int *y)
{
	mlx_put_image_to_window(mlx_sess->sess, mlx_sess->win, img, *x, *y);
	mlx_string_put(mlx_sess->sess, mlx_sess->win, 0, 0, 0x00ff0000, "Hello");
}
