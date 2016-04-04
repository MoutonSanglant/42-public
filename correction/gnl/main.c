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

	printf("== Get Next Line test program ==\n");
	line = NULL;
	if (argc <= 1)
	{
		printf("\x1B[33mTest on stdin\x1B[0m\n(press CTRL+D to stop the test)\n");
		while ((r = get_next_line(fileno(stdin), &line)))
		{
			if (r > 0)
			{
				ft_putnbr(r);
				ft_putendl(" readen characters on stdin: ");
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
		ft_putendl("======================\n");
	}
	else
	{
		printf("\x1B[33mTest on regular files\x1B[0m\n");
		printf("(press return to run test)\n");
		fpause();

		argc--;
		fd = (int *)ft_memalloc(sizeof(int) * argc);
		i = 0;
		while (i < argc)
		{
			fd[i] = open(argv[i + 1], O_RDONLY);
			i++;
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
		ft_putendl(">> End of all files <<");
		ft_putendl("======================\n");
	}

	ft_putendl("\x1B[33mExtra: test with an incorrect fd\x1B[0m");
	printf("(press return to run test)\n");
	fpause();

	int gnl_ret;

	gnl_ret = get_next_line(967, &line);
	if (gnl_ret == -1)
		ft_putendl("gnl return: \x1B[32mok\x1B[0m !");
	else
		printf("gnl return: \x1B[31mnot ok\x1B[0m !\n-> expected: -1\n-> yours: %i\n", gnl_ret);
	if (line)
		ft_memdel((void **)&line);
	ft_putendl("======================\n");
	ft_putendl("\x1B[33mMultiple fd: test with uncleared file descriptors\x1B[0m");
	printf("(press return to run test)\n");
	fpause();

	int p[2];
	int out;
	int ffd;
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
	if (strcmp(line, str) == 0)
		ft_putendl("line match: \x1B[32mok\x1B[0m !");
	else
		printf("line match: \x1B[31mnot ok\x1B[0m !\n-> expected: %s\n yours: %s\n", str, line);
	if (gnl_ret == 0 || gnl_ret == 1)
		ft_putendl("gnl return: \x1B[32mok\x1B[0m !");
	else
		printf("gnl return: \x1B[31mnot ok\x1B[0m !\n-> expected: 0 || 1\n-> yours: %i\n", gnl_ret);
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
		ft_putendl("gnl return: \x1B[32mok\x1B[0m !");
	else
		printf("gnl return: \x1B[31mnot ok\x1B[0m !\n-> expected: 1\n-> yours: %i\n", gnl_ret);
	if (ft_strcmp(line, "abc") == 0)
		ft_putendl("line match: \x1B[32mok\x1B[0m !");
	else
		printf("line match: \x1B[31mnot ok\x1B[0m !\n-> expected: abc\n yours: %s\n", line);
	ft_memdel((void **)&line);
	gnl_ret = get_next_line(p[0], &line);
	if (gnl_ret == 1)
		ft_putendl("gnl return: \x1B[32mok\x1B[0m !");
	else
		printf("gnl return: \x1B[31mnot ok\x1B[0m !\n-> expected: 1\n-> yours: %i\n", gnl_ret);
	if (line == NULL || *line =='\0')
		ft_putendl("line match: \x1B[32mok\x1B[0m !");
	else
		printf("line match: \x1B[31mnot ok\x1B[0m !\n-> expected: NULL\n yours: %s\n", line);
	ft_memdel((void **)&line);
	gnl_ret = get_next_line(p[0], &line);
	if (gnl_ret == 0)
		ft_putendl("gnl return: \x1B[32mok\x1B[0m !");
	else
		printf("gnl return: \x1B[31mnot ok\x1B[0m !\n-> expected: 0\n-> yours: %i\n", gnl_ret);
	if (line == NULL || *line =='\0')
		ft_putendl("line match: \x1B[32mok\x1B[0m !");
	else
		printf("line match: \x1B[31mnot ok\x1B[0m !\n-> expected: NULL\n yours: %s\n", line);
	ft_memdel((void **)&line);
	gnl_ret = get_next_line(p[0], &line);
	if (gnl_ret == 0)
		ft_putendl("gnl return: \x1B[32mok\x1B[0m !");
	else
		printf("gnl return: \x1B[31mnot ok\x1B[0m !\n-> expected: 0\n-> yours: %i\n", gnl_ret);
	if (line == NULL || *line =='\0')
		ft_putendl("line match: \x1B[32mok\x1B[0m !");
	else
		printf("line match: \x1B[31mnot ok\x1B[0m !\n-> expected: NULL\n yours: %s\n", line);
	ft_memdel((void **)&line);
	ft_putendl("======================\n");
	return (0);
}
