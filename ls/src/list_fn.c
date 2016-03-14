/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 20:15:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/14 21:54:58 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		remove_element(void *element, size_t size)
{
	t_file_datas	*fdatas;

	(void)size;
	fdatas = (t_file_datas *)element;
	if (fdatas->name)
		ft_strdel(&fdatas->name);
	if (fdatas->pathname)
		ft_strdel(&fdatas->pathname);
	ft_memdel((void **)&element);
}

static void		list_recursively(t_ls_datas *ls_datas, t_list *list,
									t_file_datas *p_file_data)
{
	ls_datas->flags |= _FLAG_PRINT_FOLDERS_NAME;
	while (list)
	{
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

static void		print_header_if_needed(t_ls_datas *ls_datas,
											const char *folder_name)
{
	static int		list_count = 0;

	if (list_count++)
		ft_putchar('\n');
	if (ls_datas->flags & _FLAG_PRINT_FOLDERS_NAME)
		ft_printf("%s:\n", (folder_name[0] != '\0') ? folder_name : ".");
	ls_datas->flags |= _FLAG_PRINT_FOLDERS_NAME;
}

void			list_files(t_ls_datas *ls_datas, t_list *file_list,
							const char *folder_name)
{
	t_file_datas	*p_file_data;
	t_list			*first;

	print_header_if_needed(ls_datas, folder_name);
	if (!file_list)
		return ;
	if (folder_name[0] != '\0' && ls_datas->print_fn == &print_detailed_line)
		ft_printf("total %u\n", ls_datas->total_blocks_count);
	file_list = ft_lstsort(file_list, ls_datas->sort_fn);
	if (ls_datas->time_sort_fn)
		file_list = ft_lstsort(file_list, ls_datas->time_sort_fn);
	first = file_list;
	while (file_list)
	{
		p_file_data = (t_file_datas *)file_list->content;
		ls_datas->print_fn(ls_datas, p_file_data);
		file_list = file_list->next;
	}
	if (ls_datas->flags & FLAG_BIG_R)
		list_recursively(ls_datas, first, p_file_data);
	if (first)
		ft_lstdel(&first, &remove_element);
}

int				list_directories(t_ls_datas *ls_datas)
{
	t_file_datas	*file_datas;
	t_list			*dir_list;
	int				read_e;
	int				ret_e;

	ret_e = 0;
	dir_list = ft_lstsort(ls_datas->directories, ls_datas->sort_fn);
	if (ls_datas->time_sort_fn)
		dir_list = ft_lstsort(ls_datas->directories,
										ls_datas->time_sort_fn);
	if (dir_list->next)
		ls_datas->flags |= _FLAG_PRINT_FOLDERS_NAME;
	while (dir_list)
	{
		file_datas = (t_file_datas *)dir_list->content;
		if ((read_e = read_dir(ls_datas, file_datas, file_datas->name)))
			ret_e = read_e;
		dir_list = dir_list->next;
	}
	return (ret_e);
}
