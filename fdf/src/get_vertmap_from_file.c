/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vertmap_from_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 23:38:14 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/05 22:51:23 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void				format_error(void)
{
	ft_putendl("Error: File is badly formated !'");
	exit(16);
}

/*
**	TODO
**	Format error case:
**	A line is bigger/smaller than another
*/

static float			hex_to_float(char *hex)
{
	char	a;
	char	b;

	a = 0;
	b = 0;
	if (hex[0] >= 'A' && hex[0] <= 'F')
		a = hex[0] - 'A' + 10;
	else if (hex[0] >= 'a' && hex[0] <= 'f')
		a = hex[0] - 'a' + 10;
	else if (hex[0] >= '0' && hex[0] <= '9')
		a = hex[0] - '0';
	if (hex[1] >= 'A' && hex[1] <= 'F')
		b = hex[1] - 'A' + 10;
	else if (hex[1] >= 'a' && hex[1] <= 'f')
		b = hex[1] - 'a' + 10;
	else if (hex[1] >= '0' && hex[1] <= '9')
		b = hex[1] - '0';
	return ((float)((a * 16) + b) / 255);
}

/*
**	a line is formated this way:
**	1 1 1 0 0 0 0 1 1 0 0 0 1
**	1 1 1 -1 1 1 0 1,0xFFFFFFFF 1 1 1 0
*/

static t_vert			*parse_value_array(char **ascii_values,
								t_vert *vertices, int line_nbr, int *count)
{
	char	*color;
	int		i;

	i = 0;
	while (ascii_values[i])
	{
		if (!ft_isdigit(ascii_values[i][0]))
			format_error();
		if ((color = ft_strchr(ascii_values[i], ',')))
		{
			if (ft_strlen(color) < 9)
				format_error();
			vertices[i].color.r = hex_to_float(&color[3]);
			vertices[i].color.g = hex_to_float(&color[5]);
			vertices[i].color.b = hex_to_float(&color[7]);
		}
		else
		{
			vertices[i].color.r = 1;
			vertices[i].color.g = 1.f - ((float)fminf(ft_atoi(ascii_values[i]) * 100.f, 255.f)) / 255.f;
			vertices[i].color.b = 1.f - ((float)fminf(ft_atoi(ascii_values[i]) * 100.f, 255.f)) / 255.f;
		}
		vertices[i].coord.x = i;
		vertices[i].coord.y = line_nbr;
		vertices[i].coord.z = ft_atoi(ascii_values[i]);
		*count = ++i;
	}
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

	*y = count_file_lines(path);
	if (!(vertex_map = (t_vert **)ft_memalloc(sizeof(t_vert *) * *y)))
		alloc_error("vertex_map", sizeof(t_vert *) * *y);
	i = 0;
	line = NULL;
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
	close(fd);
	return (vertex_map);
}
