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

				if (line)
					ft_memdel((void **)&line);
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
	if (line)
		ft_memdel((void **)&line);
	fpause();
	ft_putendl("Extra: test with an incorrect ???");
	fpause();

	int p[2];
	int out;
	int ffd;
	int gnl_ret;
	char *str;

	str = (char *)malloc(1000 * 1000);
	*str = '\0';
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	out = dup(1);
	pipe(p);
	dup2(p[1], 1);

	write(1, str, strlen(str));
	close(p[1]);
	dup2(out, 1);
	gnl_ret = get_next_line(p[0], &line);
	if(strcmp(line, str) == 0)
		ft_putendl("this is ok");
	if(gnl_ret == 0 || gnl_ret == 1)
		ft_putendl("this is ok");
	ft_memdel((void **)&line);
	ft_memdel((void **)&str);

/*	gnl_ret = get_next_line(p[0], &line);
	gnl_ret = get_next_line(p[0], &line);
	gnl_ret = get_next_line(p[0], &line);
	gnl_ret = get_next_line(p[0], &line);
	gnl_ret = get_next_line(p[0], &line);
	gnl_ret = get_next_line(p[0], &line);
	gnl_ret = get_next_line(p[0], &line);
	gnl_ret = get_next_line(p[0], &line);
	gnl_ret = get_next_line(p[0], &line);
	gnl_ret = get_next_line(p[0], &line);
	gnl_ret = get_next_line(p[0], &line);
	gnl_ret = get_next_line(p[0], &line);*/
	out = dup(1);
	pipe(p);

	ffd = 1;
	dup2(p[1], ffd);
	write(ffd, "abc\n\n", 5);
	close(p[1]);
	dup2(out, ffd);

	gnl_ret = get_next_line(p[0], &line);
	if (gnl_ret == 1)
		ft_putendl("1 ok !");
	if (ft_strcmp(line, "abc") == 0)
		ft_putendl("2 ok !");
	ft_memdel((void **)&line);
	gnl_ret = get_next_line(p[0], &line);
	if (gnl_ret == 1)
		ft_putendl("3 ok !");
	if (line == NULL || *line =='\0')
		ft_putendl("4 ok !");
	ft_memdel((void **)&line);
	gnl_ret = get_next_line(p[0], &line);
	if (gnl_ret == 0)
		ft_putendl("5 ok !");
	if (line == NULL || *line =='\0')
		ft_putendl("6 ok !");
	ft_memdel((void **)&line);
	gnl_ret = get_next_line(p[0], &line);
	if (gnl_ret == 0)
		ft_putendl("7 ok !");
	if (line == NULL || *line =='\0')
		ft_putendl("8 ok !");
	ft_memdel((void **)&line);
	return (0);
}
