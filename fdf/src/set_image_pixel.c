/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:50:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/20 01:40:28 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		set_image_pixel(t_image *img, int color, int x, int y)
{
	int				opp;
	int				dec;
	unsigned char	*ptr;

	opp = img->bpp / 8;
	dec = opp;

	/*
	(void) x;
	(void) y;
	(void) color;
	(void) img;
	*/
	/*
	** TODO
	** manage different endians
	*/
	ptr = ((unsigned char *)img->data + y * img->sl) + x * opp;
	while (dec--)
		*(ptr + dec) = ((unsigned char *)(&color))[dec];

}
