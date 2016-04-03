/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 02:12:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/03 20:17:45 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

#define PROGRAM_NAME "minishell"

char	**fetch_path()
{
	extern char		**environ;
	char			**out;
	char			*tmp;
	int				i;

	i = 0;
	out = NULL;
	ft_printf("initial environement:\n");
	while (environ[i])
	{
		tmp = ft_strnstr(environ[i++], "PATH", 4);
		if (tmp)
		{
			out = ft_strsplit(ft_strdup(&tmp[5]), ':');
			break;
		}
	}
	return (out);
}

void	print_env()
{
	extern char		**environ;
	int				i;

	i = 0;
	while (environ[i])
		ft_printf("%s\n", environ[i++]);
}

char	*look_in_path(char *program_name, char **path)
{
	char	*out;
	char	*full_path;
	int		amode;
	int		i;

	amode = F_OK | X_OK;
	i = 0;
	if (access(program_name, amode) >= 0)
		return (program_name);
	while (path[i])
	{
		out = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(out, program_name);
		ft_strdel(&out);
		if (access(full_path, amode) >= 0)
		{
			out = full_path;
			break;
		}
		out = NULL;
		ft_strdel(&full_path);
		i++;
	}
	return (out);
}

int		parse_command(char *command)
{
	char	**argv;
	char	**env = { NULL };
	char	**path;
	char	*program_name;
	char	*full_path;
	pid_t	fork_id;
	int		a;

	path = fetch_path();
	while (*command == ' ')
		command++;
	if (*command == '\0')
		return (0);
	else if (ft_strequ(command, "env"))
		print_env();
	else if (ft_strequ(command, "exit"))
	{
		exit(0);
	}
	argv = ft_strsplit(command, ' ');
	program_name = ft_strdup(argv[0]);
	argv[0] = ft_strdup("");
	full_path = look_in_path(program_name, path);
	if (full_path)
	{
		fork_id = fork();
		if (fork_id == 0)
		{
			if (execve(full_path, argv, env))
				ft_printf("ERROR: Something went bad...\n");
		}
		else
			wait(&a);
	}
	else
	{
		ft_printf("%s: %s: command not found\n", PROGRAM_NAME, program_name);
		return (-1);
	}
	return (0);
}

void	get_user_command(void)
{
	char	*line;

	if (get_next_line(1, &line))
	{
		parse_command(line);
		ft_strdel(&line);
	}
}

void	show_prompt(void)
{
	while (1)
	{
		ft_putstr("$> ");
		get_user_command();
	}
}

int		main(void)
{
	show_prompt();
	return (0);

	char			*cwd;
	char			buf[1024];
	//pid_t			fork_id;
	struct stat		st_stat;
	int				fd;
	char			*args[] = { "ls", "-a", "-l", "--color", NULL };
	char			*env[] = { NULL };

	cwd = getcwd(buf, 1024);
	ft_printf("Current working directory: %s\n", cwd);
	ft_printf("Buffer: %s\n", buf);
	ft_printf("Change directory to: 'toto'\n", buf);
	chdir("toto");
	cwd = getcwd(buf, 1024);
	ft_printf("Current working directory: %s\n", cwd);
	ft_printf("Buffer: %s\n", buf);
	ft_printf("Opening file: 'testfile'\n");
	fd = open("testfile", O_RDONLY);
	fstat(fd, &st_stat);
	execve("/bin/ls", args, env);
	/*
	ft_printf("Forking...\n");
	fork_id = fork();
	ft_printf("Fork %i !\n", fork_id);
	ft_printf("Number of hard links: %i\n", st_stat.st_nlink);
	*/
	return (0);
}
