/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_canvas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:54:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/03 16:59:41 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_canvas(t_mlx_sess *p, int clear_color)
{
	size_t x;
	size_t y;

	x = 0;
	y = 0;
	while (x < p->width)
	{
		while (y < p->height)
		{
			set_image_pixel(p, p->img, clear_color, x, y);
			p->zbuffer[x + y * (p->width)] = FLT_MAX;
			++y;
		}
		y = 0;
		x++;
	}
}
