/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vertmap_from_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 23:38:14 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/03 20:03:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**		TODO
**	Look at perror & strerror (functions ?)
**	If possible, return the malloc error modified (perror ?)
*/

static void		buff_error(void)
{
	ft_putendl("Error: Can't read file !");
	exit(17);
}

static void		format_error(void)
{
	ft_putendl("Error: File is badly formated !'");
	exit(16);
}

static t_vert	*parse_value_array(char **ascii_values, t_vert *vertices,
									int line_nbr, int *count)
{
	int		i;
	int		nbrlen;

	i = 0;
	while (ascii_values[i])
	{
		if (!ft_isdigit(ascii_values[i][0]))
		{
			nbrlen = ft_strlen(ascii_values[i]);
			if (nbrlen > 1 && !ft_isdigit(ascii_values[i][1]))
				format_error();
			else
				format_error();
		}
		vertices[i].coord.x = i;
		vertices[i].coord.y = line_nbr;
		vertices[i].coord.z = ft_atoi(ascii_values[i]);
		vertices[i].color.r = 0;
		vertices[i].color.g = 0;
		vertices[i].color.b = 0;
		i++;
		*count = i;
	}
	return (vertices);
}

/*
**	a line:
**	1 1 1 0 0 0 0 1 1 0 0 0 1
**	1 1 1 -1 1 1 0 1,0xFFFFFFFF 1 1 1 0
*/

static t_vert	*get_vertex_line(char *line, int line_nbr, int *count)
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
	vertices = (t_vert *)ft_memalloc(sizeof(t_vert) * i);
	vertices = parse_value_array(ascii_values, vertices, line_nbr, count);
	i = 0;
	while (ascii_values[i])
		ft_memdel((void **)&ascii_values[i++]);
	ft_memdel((void **)&ascii_values);
	return (vertices);
}

t_vert			**get_vertmap_from_file(char *path, int *x, int *y)
{
	t_vert	**vertex_map;
	char	*line;
	int		bcount;
	int		fd;
	int		i;

	*y = count_file_lines(path);
	vertex_map = (t_vert **)ft_memalloc(sizeof(t_vert *) * *y);
	i = 0;
	line = NULL;
	fd = open(path, O_RDONLY);
	while ((bcount = get_next_line(fd, &line)))
	{
		if (bcount < 0)
			buff_error();
		vertex_map[i] = get_vertex_line(line, i, x);
		ft_strdel(&line);
		i++;
	}
	close(fd);
	return (vertex_map);
}
