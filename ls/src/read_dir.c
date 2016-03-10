/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 11:41:23 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/10 17:33:29 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		store_col_width_infos(t_ls_datas *ls_datas, struct stat *st_stat)
{
	char	*username;
	char	*groupname;
	char	*str_links;
	char	*str_size;
	int		len;

	username = getpwuid(st_stat->st_uid)->pw_name;
	groupname = getgrgid(st_stat->st_gid)->gr_name;
	str_links = ft_uitoa((unsigned)st_stat->st_nlink);
	str_size = ft_uitoa((size_t)st_stat->st_size);

	len = ft_strlen(username);
	if (len > ls_datas->col_user_width)
		ls_datas->col_user_width = len;
	len = ft_strlen(groupname);
	if (len > ls_datas->col_group_width)
		ls_datas->col_group_width = len;
	len = ft_strlen(str_links);
	if (len > ls_datas->col_links_width)
		ls_datas->col_links_width = len;
	len = ft_strlen(str_size);
	if (len > ls_datas->col_size_width)
		ls_datas->col_size_width = len;

	ft_strdel(&str_links);
	ft_strdel(&str_size);
}

static t_list	*fetch_file_datas(t_ls_datas *ls_datas, char *file_name,
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
		store_col_width_infos(ls_datas, &file_data.st_stat);
		if (ret < 0)
			error_unimplemented();
		files = ft_lstnew((void *)&file_data, sizeof(t_file_datas));
		ft_strdel(&tmp);
		ft_strdel(&full_path);
	}
	return (files);
}

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
