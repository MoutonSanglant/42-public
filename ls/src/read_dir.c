/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 11:41:23 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/10 21:50:35 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				read_dir(const char *f_name, t_ls_datas *ls_datas)
{
	struct dirent	*p_dirent;
	DIR				*p_dir;
	char			*d_name;
	t_list			*files;
	t_list			*first;

	files = NULL;
	first = NULL;
	p_dir = opendir(f_name);
	if (!p_dir)
		return (error_path(f_name));
	ls_datas->col_user_width = 0;
	ls_datas->col_group_width = 0;
	ls_datas->col_links_width = 0;
	ls_datas->col_size_width = 0;
	while ((p_dirent = readdir(p_dir)))
	{
		d_name = p_dirent->d_name;
		if (files && (files->next = fetch_file_datas(ls_datas, d_name, f_name)))
			files = files->next;
		else if (!first && (first = fetch_file_datas(ls_datas, d_name, f_name)))
			files = first;
	}
	list_files(ls_datas, first, f_name);
	closedir(p_dir);
	return (0);
}
