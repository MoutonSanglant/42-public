/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 17:07:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/11 13:28:13 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	2 steps routine:
**	- fetch flags
**	- fetch directory names
*/

static int		fetch_flags(int argc, char **argv, t_ls_datas *ls_datas)
{
	char	*arg;
	int		reverse;
	int		len;
	int		i;
	int		j;

	i = 0;
	reverse = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		arg = argv[i];
		len = ft_strlen(arg);
		if (len < 2)
			break ;
		j = 0;
		while (++j < len)
		{
			if (arg[j] == 'R')
				ls_datas->flags |= FLAG_BIG_R;
			else if (arg[j] == 'a')
				ls_datas->flags |= FLAG_A;
			else if (arg[j] == 'l')
				ls_datas->print_fn = &print_detailed_line;
			else if (arg[j] == 'r')
				reverse = 1;
			else if (arg[j] == 't')
				ls_datas->flags |= FLAG_T;
			else
				error_usage(arg[j]);
		}
	}
	if (reverse)
		ls_datas->sort_fn = &sort_antilexicographic;
	return (i - 1);
}

static void		set_args(t_list **list, t_ls_datas *ls_datas,
							t_file_datas *file, int file_type,
							const char *file_name)
{
	if (*list)
	{
		if (file_type == 0)
			(*list)->next = ft_lstnew((void *)file, sizeof(t_file_datas));
		else
			(*list)->next = fetch_file_datas(ls_datas, file_name, "");
		*list = (*list)->next;
	}
	else
	{
		if (file_type == 0)
		{
			*list = ft_lstnew((void *)file, sizeof(t_file_datas));
			ls_datas->directories = *list;
		}
		else
		{
			*list = fetch_file_datas(ls_datas, file_name, "");
			ls_datas->files = *list;
		}
	}
}

void			fetch_args(int argc, char **argv, t_ls_datas *ls_datas)
{
	t_list			*dir_list;
	t_list			*files_list;
	t_file_datas	file;
	struct stat		st_stat;
	int				i;
	int				ret;

	dir_list = NULL;
	files_list = NULL;
	i = fetch_flags(argc, argv, ls_datas);
	while (--argc > i)
	{
		file.name = ft_strdup(argv[argc]);
		file.pathname = NULL;
		ret = lstat(file.name, &st_stat);
		if (ret < 0)
			error_path(file.name);
		else if (S_ISDIR(st_stat.st_mode))
			set_args(&dir_list, ls_datas, &file, 0, file.name);
		else if (S_ISREG(st_stat.st_mode))
			set_args(&files_list, ls_datas, &file, 1, file.name);
		else if (S_ISLNK(st_stat.st_mode))
			set_args(&files_list, ls_datas, &file, 1, file.name);
	}
	if (!ls_datas->directories && !files_list)
	{
		file.name = ft_strdup(".");
		ls_datas->directories = ft_lstnew((void *)&file, sizeof(t_file_datas));
	}
}

