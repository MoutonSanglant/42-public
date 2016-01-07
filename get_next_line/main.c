#include <stdio.h>
#include <fcntl.h>
#include <libft.h>

#include "get_next_line.h"

int		main(int argc, char **argv)
{
	int		i;
	int		r;
	int		*fd;
	char	*line;
	int		fd_test;

	line = NULL;
	if (argc <= 1)
	{
		while ((r = get_next_line(fileno(stdin), &line)))
		{
			if (r > 0)
			{
				ft_putstr("stdin: ");
				ft_putendl(line);
			}
			else if (r == 0)
			{
				ft_putendl("EOF");
				break;
			}
			else
			{
				ft_putendl("Memory error");
				return (1);
			}
		}
		ft_putendl("Job done.");
		return (0);
	}

	argc--;
	fd = (int *)malloc(sizeof(int) * argc);
	i = 0;
	while (i < argc)
	{
		fd[i] = open(argv[i + 1], O_RDONLY);
		i++;
	}

	(void) fd_test;
	while (1)
	{
		if (getchar())
			break;
	}
	while (1)
	{
		if (getchar())
			break;
	}
	while (1)
	{
		i = 0;
		fd_test = 0;
		while (i < argc)
		{
			if (fd[i] > 0)
				fd_test++;
			i++;
		}
		if (!fd_test)
			break;

		i = 0;
		while (i < argc)
		{
			if (i >= argc)
			{
				i = 0;
				continue;
			}
			if (fd[i] <= 0)
			{
				i++;
				continue;
			}

			r = get_next_line(fd[i], &line);
			if (r > 0)
			{
				ft_putstr("[");
				ft_putnbr(fd[i]);
				ft_putstr("] ");
				ft_putstr(argv[i + 1]);
				ft_putstr(": ");
				ft_putendl(line);
			}
			else if (r == 0)
			{
				ft_putstr(">> End of file on fd ");
				ft_putnbr(fd[i]);
				ft_putendl(" <<");
				fd[i] = -1;
				break;
			}
			else
			{
				ft_putendl("Memory error");
				return (1);
			}
			i++;
			while (1)
			{
				if (getchar())
				{
					ft_putendl("NEXT !!");
					break;
				}
			}
		}
	}
	free(line);
	line = NULL;
	ft_putendl(">> End of files <<");
	while (1)
	{
		if (getchar())
			break;
	}
	while (1)
	{
		if (getchar())
			break;
	}
	return (0);
}
