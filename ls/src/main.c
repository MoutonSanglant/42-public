/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 17:43:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/18 14:58:46 by tdefresn         ###   ########.fr       */
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

void static		check_validity(t_ls_datas *ls_datas)
{
	t_file_datas	file;
	t_list			*invalid_list;

	if (!ls_datas->directories && !ls_datas->files && !ls_datas->invalid)
	{
		file.name = ft_strdup(".");
		file.pathname = NULL;
		ls_datas->directories = ft_lstnew((void **)&file, sizeof(t_file_datas));
	}
	if (ls_datas->invalid)
	{
		ls_datas->invalid = ft_lstsort(ls_datas->invalid, &sort_lexicographic);
		invalid_list = ls_datas->invalid;
		while (invalid_list)
		{
			ls_datas->error =
				error_path(((t_file_datas *)invalid_list->content)->name);
			invalid_list = invalid_list->next;
		}
		ft_lstdel(&ls_datas->invalid, &remove_file_element);
	}
}

int				main(int argc, char **argv)
{
	t_ls_datas		ls_datas;

	ls_datas.error = 0;
	ls_datas.p_dir = NULL;
	ls_datas.files = NULL;
	ls_datas.directories = NULL;
	ls_datas.invalid = NULL;
	ls_datas.col_user_width = 0;
	ls_datas.col_group_width = 0;
	ls_datas.col_links_width = 0;
	ls_datas.col_size_width = 0;
	ls_datas.total_blocks_count = 0;
	ls_datas.flags = FLAG_NONE;
	ls_datas.print_fn = &print_one;
	ls_datas.sort_fn = &sort_lexicographic;
	fetch_args(argc, argv, &ls_datas);
	check_validity(&ls_datas);
	if (ls_datas.files)
		list_files(&ls_datas, ls_datas.files, "");
	if (ls_datas.directories)
		list_directories(&ls_datas);
	clear_ls_datas(&ls_datas);
	return (ls_datas.error);
}
