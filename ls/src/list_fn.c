/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 20:15:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/17 19:09:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		list_recursively(t_ls_datas *ls_datas, t_list *list)
{
	t_file_datas	*p_file_data;

	ls_datas->flags |= _FLAG_PRINT_FOLDERS_NAME;
	while (list)
	{
		p_file_data = (t_file_datas *)list->content;
		if (S_ISDIR(p_file_data->st_stat.st_mode))
		{
			if (p_file_data->name[0] == '.')
			{
				if ((ls_datas->flags & FLAG_A)
						&& !(p_file_data->name[1] == '.'
							|| p_file_data->name[1] == '\0'))
					read_dir(ls_datas, p_file_data, p_file_data->pathname);
			}
			else
				read_dir(ls_datas, p_file_data, p_file_data->pathname);
		}
		p_file_data = (t_file_datas *)list->content;
		list = list->next;
	}
}

void			list_files(t_ls_datas *ls_datas, t_list *file_list,
							const char *folder_name)
{
	t_file_datas	*p_file_data;
	t_list			*first;

	ls_datas->flags |= _FLAG_SEPARATOR;
	if (!file_list)
		return ;
	if (folder_name[0] != '\0' && ls_datas->print_fn == &print_detailed_line)
		ft_printf("total %u\n", ls_datas->total_blocks_count);
	file_list = ft_lstsort(file_list, ls_datas->sort_fn);
	first = file_list;
	while (file_list)
	{
		p_file_data = (t_file_datas *)file_list->content;
		ls_datas->print_fn(ls_datas, p_file_data);
		file_list = file_list->next;
	}
	if (ls_datas->flags & FLAG_BIG_R)
		list_recursively(ls_datas, first);
	if (first)
		ft_lstdel(&first, &remove_file_element);
}

void			list_directories(t_ls_datas *ls_datas)
{
	t_file_datas	*file_datas;
	t_list			*dir_list;

	ls_datas->directories =
		ft_lstsort(ls_datas->directories, ls_datas->sort_fn);
	dir_list = ls_datas->directories;
	if (dir_list->next)
		ls_datas->flags |= _FLAG_PRINT_FOLDERS_NAME;
	while (dir_list)
	{
		file_datas = (t_file_datas *)dir_list->content;
		read_dir(ls_datas, file_datas, file_datas->name);
		dir_list = dir_list->next;
	}
}
