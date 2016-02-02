/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:55:42 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/02 13:20:05 by tdefresn         ###   ########.fr       */
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

void	draw_debug_gui(t_mlx_sess *p)
{
	static char *camera[3];
	int			line_height;
	int			line;
	int			i;

	line = 1;
	line_height = 15;

	mlx_string_put(p->sess, p->win, 5, line++ * line_height, 0x00ffffff, "DEBUG CONSOLE");
	if (p->img->filename)
	{
		mlx_string_put(p->sess, p->win, 5, line * line_height, 0x00ffffff, "Source file: ");
		mlx_string_put(p->sess, p->win, 120, line++ * line_height, 0x00ffffff, p->img->filename);
	}
	mlx_string_put(p->sess, p->win, 5, line++ * line_height, 0x00ffffff, "Camera");
	if (!camera[0])
	{
		/*
		** MEMORY IS DEFINETLY LOST !!
		*/
		i = 0;
		camera[0] = (char *)ft_memalloc(sizeof(char) * 20);
		camera[0] = ft_strcpy(camera[0], "  x: ");
		camera[1] = (char *)ft_memalloc(sizeof(char) * 20);
		camera[1] = ft_strcpy(camera[1], "  y: ");
		camera[2] = (char *)ft_memalloc(sizeof(char) * 20);
		camera[2] = ft_strcpy(camera[2], "  z: ");
	}
	i = 0;
	while (i < 3)
	{
		ft_strncpy(&camera[i][5], ft_itoa((int)(*p->world)[3 + i * 4]), 3);
		camera[i][8] = '\0';
		mlx_string_put(p->sess, p->win, 5, line++ * line_height, 0x00ffffff, camera[i]);
		i++;
	}
}
