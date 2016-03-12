/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vertmap_from_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 23:38:14 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/12 11:43:47 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			str_to_color(char *hex, t_color *color)
{
	int		len;

	len = ft_strlen(hex);
	if (len < 3)
		color->b = hex_to_float(&hex[0]);
	else if (len < 5)
	{
		color->g = hex_to_float(&hex[0]);
		color->b = hex_to_float(&hex[2]);
	}
	else
	{
		color->r = hex_to_float(&hex[0]);
		color->g = hex_to_float(&hex[2]);
		color->b = hex_to_float(&hex[4]);
	}
}

static void				set_vertex_attributes(t_vert *vertex,
											char **ascii_values, int i, int y)
{
	char	*color;
	float	z;

	z = ft_atoi(ascii_values[i]);
	if ((color = ft_strchr(ascii_values[i], ',')))
		str_to_color(&color[3], &vertex->color);
	else
	{
		vertex->color.r = (z > 2) ? 0.f
					+ (fmaxf(fminf(z * 30.f, 255.f), 0)) / 255.f : 0.f;
		vertex->color.g = (z > 0) ? 1.f
					- (fminf(z * 30.f, 255.f)) / 255.f : 1.f;
		vertex->color.b = (z < -2) ? 0.f
					+ (fmaxf(fminf(-z * 30.f, 255.f), 0)) / 255.f : 0.f;
	}
	vertex->coord.x = i;
	vertex->coord.y = y;
	vertex->coord.z = z;
}

/*
**	a line is formated this way:
**	1 1 1 0 0 0 0 1 1 0 0 0 1
**	or this way:
**	1 1 1 -1 1 1 0 1,0xFFFFFFFF 1 1 1 0
*/

static t_vert			*parse_value_array(char **ascii_values,
								t_vert *vertices, int line_nbr, int *count)
{
	static	int last_count = -1;
	int			i;

	i = 0;
	while (ascii_values[i])
	{
		if (!ft_isdigit(ascii_values[i][0]) && ascii_values[i][0] != '-')
			format_error();
		set_vertex_attributes(&vertices[i], ascii_values, i, line_nbr);
		*count = i++;
	}
	if (last_count > 0 && last_count != *count)
		format_error();
	else
		last_count = *count;
	return (vertices);
}

static t_vert			*get_vertex_line(char *line, int line_nbr, int *count)
{
	char	**ascii_values;
	t_vert	*vertices;
	int		i;

	ascii_values = ft_strsplit(line, ' ');
	if (!ascii_values)
		return (NULL);
	i = 0;
	while (ascii_values[i])
		i++;
	if (!(vertices = (t_vert *)ft_memalloc(sizeof(t_vert) * i)))
		alloc_error("vertices", sizeof(t_vert) * i);
	vertices = parse_value_array(ascii_values, vertices, line_nbr, count);
	i = 0;
	while (ascii_values[i])
		ft_memdel((void **)&ascii_values[i++]);
	ft_memdel((void **)&ascii_values);
	return (vertices);
}

t_vert					**get_vertmap_from_file(char *path, int *x, int *y)
{
	t_vert	**vertex_map;
	char	*line;
	int		bcount;
	int		fd;
	int		i;

	*y = count_file_lines(path) - 1;
	if (!(vertex_map = (t_vert **)ft_memalloc(sizeof(t_vert *) * (*y + 1))))
		alloc_error("vertex_map", sizeof(t_vert *) * (*y + 1));
	i = 0;
	fd = open(path, O_RDONLY);
	while ((bcount = get_next_line(fd, &line)))
	{
		if (bcount < 0)
		{
			perror(path);
			exit(255);
		}
		vertex_map[i] = get_vertex_line(line, i, x);
		ft_strdel(&line);
		i++;
	}
	ft_strdel(&line);
	close(fd);
	return (vertex_map);
}
