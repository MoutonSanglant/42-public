/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 17:43:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/09 14:19:46 by tdefresn         ###   ########.fr       */
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
	//t_file_datas			*folder;
	t_list			*folder_list;
	t_list			*prev;
	int				error;
	int				last_error;
	const char		*folder_name;
	int				multi_folder;

	multi_folder = 0;
	ls_datas.flags = FLAG_NONE;
	ls_datas.folders = NULL;

	error = 0;
	read_args(argc, argv, &ls_datas);
	folder_list = ls_datas.folders;
	prev = folder_list;
	folder_list = ft_lstsort(prev, ls_datas.sort_fn);
	if (folder_list->next)
		multi_folder = 1;
	while (folder_list)
	{
		folder_name = ((t_file_datas *)folder_list->content)->name;
		if (multi_folder)
			ft_printf("%s:\n", (folder_name[0] != '\0') ? folder_name : ".");
		last_error = read_dir(folder_name, &ls_datas);
		if (last_error)
			error = last_error;
		prev = folder_list;
		folder_list = folder_list->next;
		ft_lstdelone(&prev, &clear_path_list);
		if (folder_list)
			ft_putchar('\n');
	}
	return (error);
}
