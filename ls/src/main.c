/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 17:43:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/09 11:57:26 by tdefresn         ###   ########.fr       */
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
**		*>> opendir (errno)
**		*>> readdir
**		*>> closedir
**		*>> stat
**		>> lstat // for symbolic links
**		*>> getpwuid
**		*>> getgrgid
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

static void		clear_path_list(void *node, size_t size)
{
	char	*str;

	(void)size;
	str = (char *)node;
	ft_strdel(&str);
}

int		main(int argc, char **argv)
{
	t_ls_datas		ls_datas;
	t_list			*path;
	t_list			*prev;
	int				error;
	int				last_error;

	ls_datas.flags = FLAG_NONE;
	ls_datas.path = NULL;

	error = 0;
	read_args(argc, argv, &ls_datas);
	path = ls_datas.path;
	while (path)
	{
		path = ft_lstsort(path, ls_datas.sort_fn);
		last_error = read_dir(path, &ls_datas);
		if (last_error)
			error = last_error;
		prev = path;
		path = path->next;
		ft_lstdelone(&prev, &clear_path_list);
	}
	return (error);
}
