/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_file_datas.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 21:50:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/17 17:23:01 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

static void		store_col_width_infos(t_ls_datas *ls_datas,
										struct stat *st_stat)
{
	char	*username;
	char	*groupname;
	char	*str_links;
	char	*str_size;
	int		len;

	ls_datas->total_blocks_count += st_stat->st_blocks;
	username = getpwuid(st_stat->st_uid)->pw_name;
	groupname = getgrgid(st_stat->st_gid)->gr_name;
	str_links = ft_uitoa((unsigned)st_stat->st_nlink);
	str_size = ft_uitoa((size_t)st_stat->st_size);
	ls_datas->col_user_width =
		max(ls_datas->col_user_width, ft_strlen(username));
	ls_datas->col_group_width =
		max(ls_datas->col_group_width, ft_strlen(groupname));
	ls_datas->col_links_width =
		max(ls_datas->col_links_width, ft_strlen(str_links));
	len = ft_strlen(str_size);
	if (S_ISCHR(st_stat->st_mode) || S_ISBLK(st_stat->st_mode))
		len = 8;
	if (len > ls_datas->col_size_width)
		ls_datas->col_size_width = len;
	ft_strdel(&str_links);
	ft_strdel(&str_size);
}

static void		set_path(t_file_datas *file_data, const char *folder_name)
{
	char			*tmp;

	if (folder_name[0] != '\0')
	{
		tmp = ft_strjoin(folder_name, "/");
		file_data->pathname = ft_strjoin(tmp, file_data->name);
		ft_strdel(&tmp);
	}
	else
		file_data->pathname = ft_strdup(file_data->name);
}

t_list			*fetch_file_datas(t_ls_datas *ls_datas, t_file_datas *file,
								const char *folder_name)
{
	t_list			*files;
	t_file_datas	file_data;
	int				ret;

	files = NULL;
	if (ls_datas->flags & FLAG_A || !(file->name[0] == '.')
			|| (file->name[0] == '.' && file->name[1] == '/'))
	{
		file_data.name = file->name;
		set_path(&file_data, folder_name);
		ret = lstat(file_data.pathname, &file_data.st_stat);
		store_col_width_infos(ls_datas, &file_data.st_stat);
		files = ft_lstnew((void *)&file_data, sizeof(t_file_datas));
		if (!files)
			error_memalloc(ls_datas);
	}
	else
		ft_strdel(&file->name);
	return (files);
}
