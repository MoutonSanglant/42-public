/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_file_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 19:52:50 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/03 20:00:47 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		buff_error(void)
{
	ft_putendl("Error: Can't read file !");
	exit(17);
}

int				count_file_lines(char *path)
{
	char	*line;
	int		bcount;
	int		fd;
	int		i;

	i = 0;
	fd = open(path, O_RDONLY);
	while ((bcount = get_next_line(fd, &line)))
	{
		if (bcount < 0)
			buff_error();
		ft_strdel(&line);
		i++;
	}
	close(fd);
	return (i);
}
