/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_debug_gui.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 14:41:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 20:41:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char		*strjoinat(const char *s1, const char *s2, int idx)
{
	char *dst;

	dst = ft_strdup(s1);
	dst[idx] = '\0';
	dst = ft_strcat(dst, s2);
	return (dst);
}

static void		draw_image_info(void *s, void *w, t_image *img, int *line)
{
	static char	*addr = NULL;
	static char	*bpp = NULL;
	static char	*sl = NULL;
	static char	*endianess = NULL;

	*line = *line - 1;
	if (!addr || !bpp || !sl || !endianess)
	{
		addr = strjoinat("Address:   0x             ",
				ft_itoa_base((uintptr_t)img->data, 16), 13);
		bpp = strjoinat("BPP:             ", ft_itoa(img->bpp), 11);
		sl = strjoinat("Line size:             ", ft_itoa(img->sl), 11);
		endianess = strjoinat("Endianess:        ", ft_itoa(img->endian), 11);
	}
	if (img->filename)
	{
		*line = *line + 1;
		mlx_string_put(s, w, 30, *line * LINE_HEIGHT, WHITE, "Source file: ");
		mlx_string_put(s, w, 155, *line * LINE_HEIGHT, WHITE, img->filename);
	}
	mlx_string_put(s, w, 30, (*line += 1) * LINE_HEIGHT, WHITE, addr);
	mlx_string_put(s, w, 30, (*line += 1) * LINE_HEIGHT, WHITE, bpp);
	mlx_string_put(s, w, 30, (*line += 1) * LINE_HEIGHT, WHITE, sl);
	mlx_string_put(s, w, 30, (*line += 1) * LINE_HEIGHT, WHITE, endianess);
	*line = *line + 1;
}

/*
**	/!\ Memory of 'camera' will be definetly lost
*/

static void		draw_camera_info(t_mlx_sess *sess, void *s, void *w, int *line)
{
	static char *camera[3];
	int			i;

	if (!camera[0])
	{
		i = 0;
		if (!(camera[0] = (char *)ft_memalloc(sizeof(char) * 20)))
			alloc_error("debug: camera[0]", sizeof(char) * 20);
		camera[0] = ft_strcpy(camera[0], "  x: ");
		if (!(camera[1] = (char *)ft_memalloc(sizeof(char) * 20)))
			alloc_error("debug: camera[1]", sizeof(char) * 20);
		camera[1] = ft_strcpy(camera[1], "  y: ");
		if (!(camera[2] = (char *)ft_memalloc(sizeof(char) * 20)))
			alloc_error("debug: camera[2]", sizeof(char) * 20);
		camera[2] = ft_strcpy(camera[2], "  z: ");
	}
	i = 0;
	while (i < 3)
	{
		ft_strncpy(&camera[i][5], ft_itoa((int)(*sess->world)[3 + i * 4]), 3);
		camera[i][8] = '\0';
		mlx_string_put(s, w, 5, *line * LINE_HEIGHT, 0x00ffffff, camera[i]);
		*line = *line + 1;
		i++;
	}
}

void			draw_debug_gui(t_mlx_sess *sess)
{
	void	*s;
	void	*w;
	int		line;

	line = 0;
	s = sess->sess;
	w = sess->win;
	mlx_string_put(s, w, 5, line++ * LINE_HEIGHT, 0x00ffffff, "DEBUG CONSOLE");
	mlx_string_put(s, w, 5, line++ * LINE_HEIGHT, 0x00ffffff, "Image");
	draw_image_info(s, w, sess->img, &line);
	mlx_string_put(s, w, 5, line++ * LINE_HEIGHT, 0x00ffffff, "Camera");
	draw_camera_info(sess, s, w, &line);
}
