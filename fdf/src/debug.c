/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:55:42 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/18 18:15:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	output_image_info(t_image *image)
{
	ft_putstr("Image addr: ");
	ft_putaddr(image->data);
	ft_putstr("\nbpp: ");
	ft_putnbr(image->bpp);
	ft_putstr("\nsl: ");
	ft_putnbr(image->sl);
	ft_putstr("\nendian: ");
	ft_putnbr(image->endian);
	ft_putchar('\n');
}
