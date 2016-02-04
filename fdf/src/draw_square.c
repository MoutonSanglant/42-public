/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:54:27 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 19:56:57 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_square(t_mlx_sess *p, int color, t_vec2f *from, t_vec2f *to)
{
	t_vec2ui32	xy;

	xy.x = from->x;
	while (xy.x < to->x)
	{
		xy.y = from->y;
		while (xy.y < to->y)
		{
			set_image_pixel(p, p->img, color, &xy);
			xy.y++;
		}
		xy.x++;
	}
}
