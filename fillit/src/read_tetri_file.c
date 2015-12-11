/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tetri_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 12:51:30 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/11 14:18:40 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Optimal buff size is: size of (one tetriminos + 5 *\n) * max (546)
*/
#define BUFSIZE 546

char*	read_tetri_file(char *path)
{
	int		fd;
	int		bcount;
	char	*buffer;

	buffer = NULL;
	fd = open(path, O_RDONLY);
	if (fd)
	{
		buffer = (char *)malloc(sizeof(char) * BUFSIZE);
		if (!buffer)
			return (NULL);
		bcount = read(fd, buffer, BUFSIZE);
		if (bcount > 0 && bcount < BUFSIZE)
			buffer[bcount] = '\0';
		else
			ft_memdel((void **)&buffer);
	}

	return (buffer);
}
