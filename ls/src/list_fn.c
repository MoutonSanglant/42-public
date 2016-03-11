/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 20:15:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/11 10:30:38 by tdefresn         ###   ########.fr       */
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
	static int		list_count = 0;
	t_file_datas	*p_file_data;
	t_list			*prev_element;

	if (!file_list)
		return ;
	if (list_count++)
		ft_putchar('\n');
	if (ls_datas->flags & _FLAG_PRINT_FOLDERS_NAME)
		ft_printf("%s:\n", (folder_name[0] != '\0') ? folder_name : ".");
	if (ls_datas->print_fn == &print_detailed_line)
		ft_printf("total %u\n", 42);
	file_list = ft_lstsort(file_list, ls_datas->sort_fn);
	prev_element = file_list;
	while (file_list)
	{
		p_file_data = (t_file_datas *)file_list->content;
		ls_datas->print_fn(ls_datas, p_file_data);
		prev_element = file_list;
		file_list = file_list->next;
		ft_lstdelone(&prev_element, &remove_element);
	}
	ls_datas->flags |= _FLAG_PRINT_FOLDERS_NAME;
}

int				list_directories(t_ls_datas *ls_datas)
{
	t_list			*directory_list;
	t_list			*prev_element;
	const char		*file_name;
	int				read_error;
	int				ret_error;

	ret_error = 0;
	directory_list = ft_lstsort(ls_datas->directories, ls_datas->sort_fn);
	prev_element = directory_list;
	if (directory_list->next)
		ls_datas->flags |= _FLAG_PRINT_FOLDERS_NAME;
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
