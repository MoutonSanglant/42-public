/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vertmap_from_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 23:38:14 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 02:57:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** TODO
** Look at perror & strerror (functions ?)
** If possible, return the malloc error modified (perror ?)
*/
static void	buff_error()
{
	ft_putendl("Error: Can't read file !");
	exit(17);
}

static void	format_error()
{
	ft_putendl("Error: File is badly formated !'");
	exit(16);
}

/*
** a line:
** 1 1 1 0 0 0 0 1 1 0 0 0 1
**
** 1 1 1 -1 1 1 0 1,0xFFFFFFFF 1 1 1 0
*/
static t_vert	*get_vertex_line(char *line, int line_nbr, int *count)
{
	char	**ascii_values;
	t_vert	*vertices;
	int		i;
	int		nbrlen;

	ascii_values = ft_strsplit(line, ' ');
	if (!ascii_values)
		return (NULL);

	i = 0;
	while (ascii_values[i])
		i++;

	vertices = (t_vert *)ft_memalloc(sizeof(t_vert) * i);

	i = 0;
	while (ascii_values[i])
	{
		if (!ft_isdigit(ascii_values[i][0]))
		{
			nbrlen = ft_strlen(ascii_values[i]);
			if (nbrlen > 1)
			{
				if (!ft_isdigit(ascii_values[i][1]))
					format_error();
			}
			else
				format_error();
		}
		vertices[i].coord.x = i;
		vertices[i].coord.y = line_nbr;
		vertices[i].coord.z = ft_atoi(ascii_values[i]);
		vertices[i].color = 0;
		i++;
		*count = i;
	}
	ft_putstr("x: ");
	ft_putnbr(*count);
	ft_putchar('\n');

	// Clear the table
	i = 0;
	while (ascii_values[i])
	{
		ft_memdel((void **) &ascii_values[i]);
		i++;
	}
	ft_memdel((void **) &ascii_values);

	return (vertices);
}

t_vert	**get_vertmap_from_file(char *path, int *x, int *y)
{
	t_vert	**vertex_map;
	char	*line;
	int		bcount;
	int		fd;
	int		i;

	line = NULL;
	i = 0;
	fd = open(path, O_RDONLY);
	while ((bcount = get_next_line(fd, &line)))
	{
		if (bcount < 0)
			buff_error();
		ft_strdel(&line);
		i++;
	}
	*y = i;
	vertex_map = (t_vert **)ft_memalloc(sizeof(t_vert *) * *y);

	fd = open(path, O_RDONLY);
	i = 0;
	while ((bcount = get_next_line(fd, &line)))
	{
		if (bcount < 0)
			buff_error();
		ft_putendl(line);
		vertex_map[i] = get_vertex_line(line, i, x);
		ft_strdel(&line);
		i++;
	}
	return (vertex_map);
}
