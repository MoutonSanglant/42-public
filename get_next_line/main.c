#include <stdio.h>
#include <fcntl.h>
#include <libft.h>

#include "get_next_line.h"

void	fpause()
{
	while (1)
	{
		if (getchar())
			break;
	}
}

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
				ft_memdel((void **)&line);
			}
			else if (r == 0)
			{
				ft_putendl("EOF");
				if (line)
					ft_memdel((void **)&line);
				break;
			}
			else
			{
				ft_putendl("Memory error");
				return (1);
			}
		}
		if (line)
			ft_memdel((void **)&line);
	}
	else
	{
		argc--;
		fd = (int *)ft_memalloc(sizeof(int) * argc);
		i = 0;
		while (i < argc)
		{
			fd[i] = open(argv[i + 1], O_RDONLY);
			i++;
		}

		fpause();

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
					ft_memdel((void **)&line);
				}
				else if (r == 0)
				{
					ft_putstr(">> End of file on fd ");
					ft_putnbr(fd[i]);
					ft_putendl(" <<");
					fd[i] = -1;
					if (line)
						ft_memdel((void **)&line);
					continue;
				}
				else
				{
					ft_putendl("Memory error");
					return (1);
				}
				i++;
				/*
				** line-by-line mode
				fpause();
				*/
			}
			if (line)
				ft_memdel((void **)&line);
		}
		ft_memdel((void **)&fd);
		ft_putendl(">> End of files <<");
	}
	ft_putendl("Job done.");

	fpause();
	ft_putendl("Extra: test with an incorrect fd");
	fpause();
	if (get_next_line(967, &line) == -1)
		ft_putendl("OK !");
	else
		ft_putendl("Erreur, le resultat devrait etre -1.");
	fpause();
	ft_putendl("Extra: test with an incorrect ???");
	fpause();

	int p[2];
	int out;
	int ffd;

	out = dup(1);
	pipe(p);

	ffd = 1;
	dup2(p[1], 1);
	write(ffd, "oiuytrew\n", 9);
	close(p[1]);
	dup2(out, ffd);
	get_next_line(p[0], &line);
	if (ft_strcmp(line, "oiuytrew") == 0)
		ft_putendl("ok !");
	return (0);
}
