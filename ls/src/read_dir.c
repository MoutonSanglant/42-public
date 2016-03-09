/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 11:41:23 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/09 11:58:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		clear_file_list(void *node, size_t size)
{
	t_file_datas *file_data;

	(void) size;
	file_data = (t_file_datas *)node;
	//ft_printf("abc: %s\n", file_data->file);
	ft_memdel((void **)&file_data);
	//ft_memdel(&node);
}


/*
**	Degueulasse...
**	A reecrire, ainsi que ft_lstsort ! :)
*/
int		read_dir(t_list *path, t_ls_datas *ls_datas)
{
	struct dirent	*p_dirent;
	DIR				*p_dir;
	char			*d_name;
	char			*full_path;
	char			*tmp;
	t_list			*list;
	t_list			*list_start;
	t_file_datas	file_data;
	t_file_datas	*p_file_data;
	int				ret;

	list = NULL;
	list_start = NULL;
	p_dir = opendir((char *)path->content);
	if (!p_dir)
		return (error_path((char *)path->content));
	// Should output only when multiple folders
	// are inputed
//	if (((char *)path->content)[0] != '.')
//		ft_printf("%s: \n", (char *)path->content);
	while ((p_dirent = readdir(p_dir)))
	{
		d_name = p_dirent->d_name;
		if (!list)
		{
			if (d_name[0] != '.' || ls_datas->flags & FLAG_A)
			{
				file_data.file = d_name;
				// Prefix is missing, so we can't read subfolders until we
				// specify the whole path from the current directory
				full_path = ft_strjoin((char *)path->content, "/");
				tmp = full_path;
				full_path = ft_strjoin(full_path, d_name);
				ret = stat(full_path, &file_data.st_stat);
				if (ret < 0)
					error_unimplemented();
				list = ft_lstnew((void *)&file_data, sizeof(t_file_datas));
				ft_strdel(&tmp);
				ft_strdel(&full_path);
			}
				//list = ft_lstnew((void *)d_name, sizeof(char) * (ft_strlen(d_name) + 1));
		}
		else
		{
			if (d_name[0] != '.' || ls_datas->flags & FLAG_A)
			{
				file_data.file = d_name;
				// Prefix is missing, so we can't read subfolders until we
				// specify the whole path from the current directory
				full_path = ft_strjoin((char *)path->content, "/");
				tmp = full_path;
				full_path = ft_strjoin(full_path, d_name);
				ret = stat(full_path, &file_data.st_stat);
				//ret = stat(d_name, &file_data.stat);
				if (ret < 0)
					error_unimplemented();
				list->next = ft_lstnew((void *)&file_data, sizeof(t_file_datas));
				//list->next = ft_lstnew((void *)d_name, sizeof(char) * (ft_strlen(d_name) + 1));
				list = list->next;
				ft_strdel(&tmp);
				ft_strdel(&full_path);
			}
		}
		if (!list_start)
			list_start = list;
	}
	if (list)
		list = ft_lstsort(list_start, ls_datas->sort_fn);
	list_start = list;
	while (list)
	{
		p_file_data = (t_file_datas *)list->content;
		ls_datas->print_fn(p_file_data);
		list = list->next;
		/*
		**	Memory is not freed yet (should use lstdel)
		*/
	}
	ft_lstdel(&list_start, &clear_file_list);
	closedir(p_dir);
	return (0);
}
