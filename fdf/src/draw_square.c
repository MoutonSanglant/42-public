/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:54:27 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/03 18:07:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_square(t_mlx_sess *p, int color, t_vec2f *from, t_vec2f *to)
{
	int		x;
	int		y;

	x = from->x;
	while (x < to->x)
	{
		y = from->y;
		while (y < to->y)
			set_image_pixel(p, p->img, color, x, y++);
		x++;
	}
}
