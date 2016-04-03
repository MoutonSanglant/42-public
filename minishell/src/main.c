/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 02:12:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/24 15:41:50 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

#define PROGRAM_NAME "minishell"

int		parse_command(char *command)
{
	char	**argv;
	char	*program_name;
	char	**env = { NULL };
	int		amode;
	pid_t	fork_id;
	int		a;

	while (*command == ' ')
		command++;
	if (*command == '\0')
		return (0);
	argv = ft_strsplit(command, ' ');
	program_name = ft_strdup(argv[0]);
	argv[0] = ft_strdup("");
	amode = F_OK | X_OK;
	if (access(program_name, amode) < 0)
	{
		ft_printf("%s: %s: command not found\n", PROGRAM_NAME, program_name);
		return (-1);
	}
	else
	{
		fork_id = fork();
		if (fork_id == 0)
		{
			if (execve(program_name, argv, env))
				ft_printf("ERROR: Something went bad...\n");
		}
		else
			wait(&a);
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
