/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 15:19:26 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/10 16:29:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fcntl.h>
#include <unistd.h>

/*
** Optimal buff size is: size of (one tetriminos + 5 *\n) * max (546)
*/
//#define BUFSIZE 512
#define BUFSIZE 546

void	fillit_error(void)
{
	ft_putendl("error");
	exit(1);
}

void	read_file(char *path)
{
	int		fd;
	int		bcount;
	char	buffer[BUFSIZE];

	fd = open(path, O_RDONLY);
	if (fd)
	{
		bcount = read(fd, buffer, BUFSIZE);
		if (bcount > 0 && bcount < BUFSIZE)
		{
			//if (bcount >= BUFSIZE)
			//	fillit_error();
			buffer[bcount] = '\0';
			ft_putendl(buffer);
		}
		else
			fillit_error();
	}
	else
		fillit_error();
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		fillit_error();
	read_file(argv[1]);
	return (0);
}
