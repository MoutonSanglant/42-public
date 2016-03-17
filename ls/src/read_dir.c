/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 11:41:23 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/17 16:34:11 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		reset_format_infos(t_ls_datas *ls_datas)
{
	ls_datas->col_user_width = 0;
	ls_datas->col_group_width = 0;
	ls_datas->col_links_width = 0;
	ls_datas->col_size_width = 0;
	ls_datas->total_blocks_count = 0;
}

void			read_dir(t_ls_datas *ls_d, t_file_datas *file_datas,
							const char *f_name)
{
	struct dirent	*p;
	DIR				*p_dir;
	t_list			*list;
	t_list			*first;
	t_file_datas	file;

	list = NULL;
	first = NULL;
	if (!(p_dir = opendir(f_name)))
	{
		ls_d->error = error_path(file_datas->name);
		return ;
	}
	reset_format_infos(ls_d);
	while ((p = readdir(p_dir)))
	{
		file.name = ft_strdup(p->d_name);
		if (list && (list->next = fetch_file_datas(ls_d, &file, f_name)))
			list = list->next;
		else if (!first && (first = fetch_file_datas(ls_d, &file, f_name)))
			list = first;
	}
	list_files(ls_d, first, f_name);
	closedir(p_dir);
}
