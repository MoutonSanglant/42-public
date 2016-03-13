/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_file_datas.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 21:50:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/13 10:57:06 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

t_list			*fetch_file_datas(t_ls_datas *ls_datas, const char *file_name,
								const char *folder_name)
{
	t_list			*files;
	char			*tmp;
	t_file_datas	file_data;
	int				ret;

	files = NULL;
	if (file_name[0] != '.' || ls_datas->flags & FLAG_A)
	{
		file_data.name = (char *)file_name;
		if (folder_name[0] != '\0')
		{
			file_data.pathname = ft_strjoin(folder_name, "/");
			tmp = file_data.pathname;
			file_data.pathname = ft_strjoin(tmp, file_name);
			ft_strdel(&tmp);
		}
		else
			file_data.pathname = ft_strdup((char *)file_name);
		ret = lstat(file_data.pathname, &file_data.st_stat);
		if (ret < 0)
			error_unimplemented();
		store_col_width_infos(ls_datas, &file_data.st_stat);
		files = ft_lstnew((void *)&file_data, sizeof(t_file_datas));
	}
	return (files);
}
