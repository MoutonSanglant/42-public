/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 20:15:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/09 20:57:41 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		remove_element(void *element, size_t size)
{
	(void)size;
	ft_strdel((char **)&element);
}

void			list_files(t_ls_datas *ls_datas, t_list *file_list,
							const char *folder_name)
{
	static int		multi = 0;
	t_list			*prev_element;
	t_file_datas	*p_file_data;

	if (!file_list)
		return ;
	if (multi++)
		ft_printf("\n%s:\n", (folder_name[0] != '\0') ? folder_name : ".");
	file_list = ft_lstsort(file_list, ls_datas->sort_fn);
	prev_element = file_list;
	while (file_list)
	{
		p_file_data = (t_file_datas *)file_list->content;
		ls_datas->print_fn(p_file_data);
		prev_element = file_list;
		file_list = file_list->next;
		ft_lstdelone(&prev_element, &remove_element);
	}
}

int				list_directories(t_ls_datas *ls_datas)
{
	const char		*file_name;
	t_list			*directory_list;
	t_list			*prev_element;
	int				read_error;
	int				ret_error;

	ret_error = 0;
	directory_list = ft_lstsort(ls_datas->directories, ls_datas->sort_fn);
	prev_element = directory_list;
	while (directory_list)
	{
		file_name = ((t_file_datas *)directory_list->content)->name;
		if ((read_error = read_dir(file_name, ls_datas)))
			ret_error = read_error;
		prev_element = directory_list;
		directory_list = directory_list->next;
		ft_lstdelone(&prev_element, &remove_element);
	}
	return (ret_error);
}
