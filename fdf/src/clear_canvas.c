/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_canvas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:54:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/14 12:41:10 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#ifdef BONUS

void	clear_canvas(t_mlx_sess *p, int clear_color)
{
	t_vec2ui32	xy;

	xy.x = 0;
	while (xy.x < p->width)
	{
		xy.y = 0;
		while (xy.y < p->height)
		{
			set_image_pixel(p, p->img, clear_color, &xy);
			p->zbuffer[xy.x + xy.y * (p->width)] = FLT_MAX;
			xy.y++;
		}
		xy.x++;
	}
}

#else

void	clear_canvas(t_mlx_sess *p, int clear_color)
{
	t_vec2ui32	xy;

	xy.x = 0;
	while (xy.x < p->width)
	{
		xy.y = 0;
		while (xy.y < p->height)
		{
			set_image_pixel(p, p->img, clear_color, &xy);
			xy.y++;
		}
		xy.x++;
	}
}

#endif
