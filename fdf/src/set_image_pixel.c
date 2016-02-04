/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:50:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 19:55:09 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	TODO
**	Manage different endians
**	(It should help to remove the void cast on 'sess')
*/

void		set_image_pixel(t_mlx_sess *sess, t_image *img, int color,
							t_vec2ui32 *xy)
{
	int				opp;
	int				dec;
	unsigned char	*ptr;

	(void)sess;
	opp = img->bpp / 8;
	dec = opp;
	ptr = ((unsigned char *)img->data + xy->y * img->sl) + xy->x * opp;
	while (dec--)
		*(ptr + dec) = ((unsigned char *)(&color))[dec];
}
