/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 20:15:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/13 17:48:45 by tdefresn         ###   ########.fr       */
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
		p_file_data = (t_file_datas *)list->content;
		if (p_file_data->name[0] != '.'
				&& S_ISDIR(p_file_data->st_stat.st_mode))
			read_dir(p_file_data->pathname, ls_datas);
		list = list->next;
	}
}

/*
**	ATTENTION !! Sur linux le "total" n'apparait pas pour le dossier
**	./includes car celui-ci est vide. Vérifier quel est le comportement
**	de ls sur OSX et si le résultat est similaire, échanger les
**	lignes 61-62 avec les lignes 63-64
*/
void			list_files(t_ls_datas *ls_datas, t_list *file_list,
							const char *folder_name)
{
	static int		list_count = 0;
	t_file_datas	*p_file_data;
	t_list			*first;

	if (list_count++)
		ft_putchar('\n');
	if (ls_datas->flags & _FLAG_PRINT_FOLDERS_NAME)
		ft_printf("%s:\n", (folder_name[0] != '\0') ? folder_name : ".");
	if (!file_list)
		return ;
	if (ls_datas->print_fn == &print_detailed_line)
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
	t_list			*directory_list;
	const char		*file_name;
	int				read_error;
	int				ret_error;

	ret_error = 0;
	directory_list = ft_lstsort(ls_datas->directories, ls_datas->sort_fn);
	if (ls_datas->time_sort_fn)
		directory_list = ft_lstsort(ls_datas->directories,
										ls_datas->time_sort_fn);
	if (directory_list->next)
		ls_datas->flags |= _FLAG_PRINT_FOLDERS_NAME;
	while (directory_list)
	{
		file_name = ((t_file_datas *)directory_list->content)->name;
		if ((read_error = read_dir(file_name, ls_datas)))
			ret_error = read_error;
		directory_list = directory_list->next;
	}
	return (ret_error);
}
