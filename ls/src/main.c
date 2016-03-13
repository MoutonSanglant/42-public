/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 17:43:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/13 17:38:12 by tdefresn         ###   ########.fr       */
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

int				main(int argc, char **argv)
{
	t_ls_datas		ls_datas;
	int				error;

	error = 0;
	ls_datas.p_dir = NULL;
	ls_datas.files = NULL;
	ls_datas.directories = NULL;
	ls_datas.col_user_width = 0;
	ls_datas.col_group_width = 0;
	ls_datas.col_links_width = 0;
	ls_datas.col_size_width = 0;
	ls_datas.total_blocks_count = 0;
	ls_datas.flags = FLAG_NONE;
	ls_datas.print_fn = &print_one;
	ls_datas.sort_fn = &sort_lexicographic;
	ls_datas.time_sort_fn = NULL;
	fetch_args(argc, argv, &ls_datas);
	if (ls_datas.files)
		list_files(&ls_datas, ls_datas.files, "");
	if (ls_datas.directories)
		error = list_directories(&ls_datas);
	clear_ls_datas(&ls_datas);
	return (error);
}
