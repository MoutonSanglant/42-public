/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 17:07:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/17 19:11:14 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	2 steps routine:
**	- fetch flags
**	- fetch directory names
*/

static void		fetch_param_flags(t_ls_datas *ls_datas, char *arg,
									int length, int *reverse)
{
	int		j;

	j = 0;
	while (++j < length)
	{
		if (arg[j] == 'R')
			ls_datas->flags |= FLAG_BIG_R;
		else if (arg[j] == 'a')
			ls_datas->flags |= FLAG_A;
		else if (arg[j] == 'l')
		{
			ls_datas->flags |= FLAG_L;
			ls_datas->print_fn = &print_detailed_line;
		}
		else if (arg[j] == 'r')
			*reverse = 1;
		else if (arg[j] == 't')
		{
			ls_datas->flags |= FLAG_T;
			ls_datas->sort_fn = &sort_time;
		}
		else if (arg[j] == '1')
			;
		else
			error_usage(arg[j], ls_datas);
	}
}

static int		fetch_flags(int argc, char **argv, t_ls_datas *ls_datas)
{
	char	*arg;
	int		reverse;
	int		len;
	int		i;

	i = 0;
	reverse = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		arg = argv[i];
		len = ft_strlen(arg);
		if (argv[i][1] == '-')
		{
			if (argv[i][2] != '\0')
				error_usage(argv[i][1], ls_datas);
			i++;
			break;
		}
		if (len < 2)
			break ;
		fetch_param_flags(ls_datas, arg, len, &reverse);
	}
	if (reverse && ls_datas->flags & FLAG_T)
		ls_datas->sort_fn = &sort_time_reverse;
	else if (reverse)
		ls_datas->sort_fn = &sort_antilexicographic;
	return (i - 1);
}

static void		add_file(t_ls_datas *ls_datas, t_file_datas *file,
								t_list **list, int target)
{
	if (*list)
	{
		(*list)->next =
			(target == 0) ? fetch_file_datas(ls_datas, file, "") :
				ft_lstnew((void *)file, sizeof(t_file_datas));
		*list = (*list)->next;
	}
	else
	{
		if (target == 0)
		{
			*list = fetch_file_datas(ls_datas, file, "");
			ls_datas->files = *list;
		}
		else if (target == 1)
		{
			*list = ft_lstnew((void *)file, sizeof(t_file_datas));
			ls_datas->directories = *list;
		}
		else
		{
			*list = ft_lstnew((void *)file, sizeof(t_file_datas));
			ls_datas->invalid = *list;
			ls_datas->flags |= _FLAG_PRINT_FOLDERS_NAME;
		}
	}
}

void			fetch_args(int argc, char **argv, t_ls_datas *ls_datas)
{
	t_list			*dir_list;
	t_list			*files_list;
	t_list			*invalid_list;
	t_file_datas	file;
	struct stat		st_stat;
	int				flag_count;
	DIR				*p_dir;
	int				ret;

	dir_list = NULL;
	files_list = NULL;
	invalid_list = NULL;
	flag_count = fetch_flags(argc, argv, ls_datas);
	while (--argc > flag_count)
	{
		file.pathname = NULL;
		file.name = ft_strdup(argv[argc]);
		ret = lstat(file.name, &st_stat);
		if (ret < 0)
		{
			if (file.name[0] == '\0')
				exit (error_path("fts_open"));
			add_file(ls_datas, &file, &invalid_list, 2);
		}
		else
		{
			p_dir = opendir(file.name);
			if (S_ISREG(st_stat.st_mode))
				add_file(ls_datas, &file, &files_list, 0);
			else if (S_ISLNK(st_stat.st_mode))
			{
				if (ls_datas->flags & FLAG_L || !(p_dir = opendir(file.name)))
					add_file(ls_datas, &file, &files_list, 0);
				else
					add_file(ls_datas, &file, &dir_list, 1);
			}
			else
				add_file(ls_datas, &file, &dir_list, 1);
			if (p_dir)
				closedir(p_dir);
		}
	}
	if (!ls_datas->directories && !files_list && !ls_datas->invalid)
	{
		file.name = ft_strdup(".");
		file.pathname = NULL;
		add_file(ls_datas, &file, &dir_list, 1);
	}
	if (ls_datas->invalid)
	{
		ls_datas->invalid = ft_lstsort(ls_datas->invalid, &sort_lexicographic);
		invalid_list = ls_datas->invalid;
		while (invalid_list)
		{
			ls_datas->error = error_path(((t_file_datas *)invalid_list->content)->name);
			invalid_list = invalid_list->next;
		}
		ft_lstdel(&ls_datas->invalid, &remove_file_element);
	}
}
