/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_file_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 19:52:50 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/14 12:27:36 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		{
			perror(path);
			exit(255);
		}
		ft_strdel(&line);
		i++;
	}
	ft_strdel(&line);
	close(fd);
	return (i);
}
