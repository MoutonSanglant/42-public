/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 11:41:23 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/09 23:59:33 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*abc(t_ls_datas *ls_datas, char *file_name,
							const char *folder_name)
{
	t_list			*files;
	char			*full_path;
	char			*tmp;
	t_file_datas	file_data;
	int				ret;

	files = NULL;
	if (file_name[0] != '.' || ls_datas->flags & FLAG_A)
	{
		file_data.name = file_name;
		full_path = ft_strjoin(folder_name, "/");
		tmp = full_path;
		full_path = ft_strjoin(full_path, file_name);
		ret = stat(full_path, &file_data.st_stat);
		if (ret < 0)
			error_unimplemented();
		files = ft_lstnew((void *)&file_data, sizeof(t_file_datas));
		ft_strdel(&tmp);
		ft_strdel(&full_path);
	}
	return (files);
}

int				read_dir(const char *folder_name, t_ls_datas *ls_datas)
{
	struct dirent	*p_dirent;
	DIR				*p_dir;
	char			*d_name;
	t_list			*files;
	t_list			*first;

	files = NULL;
	first = NULL;
	p_dir = opendir(folder_name);
	if (!p_dir)
		return (error_path(folder_name));
	while ((p_dirent = readdir(p_dir)))
	{
		d_name = p_dirent->d_name;
		if (files && (files->next = abc(ls_datas, d_name, folder_name)))
			files = files->next;
		else if (!first && (first = abc(ls_datas, d_name, folder_name)))
			files = first;
	}
	list_files(ls_datas, first, folder_name);
	closedir(p_dir);
	return (0);
}
