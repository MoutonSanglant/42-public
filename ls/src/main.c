/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 17:43:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/05 17:46:23 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	ls params:
**	-l		List			List in long format (show files details)
**	-R		Recusive		Recursively list subdirectories encountered
**	-a		Hidden files	Print entries beginning with a '.'
**	-r		Reverse			Print in reverse order (lexi or creation)
**	-t		Sort: time		Sort by modification time (recent first) then lexi
**	=============
**	no ACL
**	-l & -R first
**	=============
**	Authorized functions:
**		write
**		>> opendir (errno)
**		>> readdir
**		>> closedir
**		>> stat
**		>> lstat
**		>> getpwuid
**		>> getgrgid
**		>> listxattr
**		>> getxattr
**		time
**		>> ctime
**		>> readlink
**		malloc
**		free
**		perror
**		strerror
**		exit
*/

/*
**	2 steps routine:
**	- read flags
**	- read paths
*/

static int		read_flags(int argc, char **argv, t_ls_datas *ls_datas)
{
	int		i;
	int		j;
	int		len;
	char	*arg;

	i = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		arg = argv[i];
		len = ft_strlen(arg);
		if (len < 2)
			break ;
		j = 0;
		while (++j < len)
		{
			if (arg[j] == 'R')
				ls_datas->flags |= FLAG_BIG_R;
			else if (arg[j] == 'a')
				ls_datas->flags |= FLAG_A;
			else if (arg[j] == 'l')
				ls_datas->flags |= FLAG_L;
			else if (arg[j] == 'r')
				ls_datas->flags |= FLAG_R;
			else if (arg[j] == 't')
				ls_datas->flags |= FLAG_T;
			else
				error_usage(arg[j]);
		}
	}
	return (i - 1);
}

static void		read_args(int argc, char **argv, t_ls_datas *ls_datas)
{
	t_list	*path;
	char	*tmp;
	char	*arg;
	int		i;

	i = read_flags(argc, argv, ls_datas);
	while (++i < argc)
	{
		arg = argv[i];
		if ((tmp = ft_strdup(arg)))
		{
			path = ft_lstnew((void *)tmp, sizeof(char *) * (ft_strlen(tmp) + 1));
			if (ls_datas->path)
				ft_lstadd(&ls_datas->path, path);
			else
				ls_datas->path = path;
			ft_strdel(&tmp);
		}
	}
	if (!ls_datas->path)
		ls_datas->path = ft_lstnew((void *)".", sizeof(char *) * 2);
}

void	read_dir(t_list *path)
{
	DIR		*p_dir;
	struct dirent	*p_dirent;

	p_dir = opendir((char *)path->content);
	if (!p_dir)
	{
		ft_printf("Cannot open directory: %s\n", (char *)path->content);
		return ;
		//error();
	}
	ft_printf("%s: \n", (char *)path->content);
	while ((p_dirent = readdir(p_dir)))
		ft_printf("%s\n", p_dirent->d_name);
	closedir(p_dir);
}

int		main(int argc, char **argv)
{
	t_ls_datas		ls_datas;
	t_list			*path;

	read_args(argc, argv, &ls_datas);
	path = ls_datas.path;
	while (path)
	{
		read_dir(path);
		path = path->next;
	}
	return (0);
}
