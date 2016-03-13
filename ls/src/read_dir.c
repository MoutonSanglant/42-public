/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 11:41:23 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/13 11:18:02 by tdefresn         ###   ########.fr       */
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

int				read_dir(const char *f_name, t_ls_datas *ls_d)
{
	struct dirent	*p;
	DIR				*p_dir;
	t_list			*list;
	t_list			*first;

	list = NULL;
	first = NULL;
	p_dir = opendir(f_name);
	if (!p_dir)
		return (error_path(f_name));
	reset_format_infos(ls_d);
	while ((p = readdir(p_dir)))
	{
		if (list && (list->next = fetch_file_datas(ls_d, p->d_name, f_name)))
			list = list->next;
		else if (!first && (first = fetch_file_datas(ls_d, p->d_name, f_name)))
			list = first;
	}
	list_files(ls_d, first, f_name);
	closedir(p_dir);
	return (0);
}
