/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 17:07:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/10 18:49:11 by tdefresn         ###   ########.fr       */
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
static void		store_col_width_infos(t_ls_datas *ls_datas, const struct stat *st_stat)
{
	char	*username;
	char	*groupname;
	char	*str_links;
	char	*str_size;
	int		len;

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


/*
** Some rework needed here, since fetch_file_datas
**	is also existing in read_dir
*/
static t_list	*fetch_file_datas(t_ls_datas *ls_datas, const char *file_name,
							const char *folder_name)
{
	t_list			*files;
	char			*full_path;
	char			*tmp;
	t_file_datas	file_data;
	int				ret;

	files = NULL;
	if (file_name[0] != '.' || ls_datas->flags & FLAG_A)
	{
		file_data.name = (char *)file_name;
		if (folder_name[0] != '\0')
		{
			full_path = ft_strjoin(folder_name, "/");
			tmp = full_path;
			full_path = ft_strjoin(full_path, file_name);
		}
		else
			full_path = (char *)file_name;
		ret = stat(full_path, &file_data.st_stat);
		if (ret < 0)
			error_unimplemented();
		store_col_width_infos(ls_datas, &file_data.st_stat);
		if (ret < 0)
			error_unimplemented();
		files = ft_lstnew((void *)&file_data, sizeof(t_file_datas));
		if (folder_name[0] != '\0')
		{
			ft_strdel(&tmp);
			ft_strdel(&full_path);
		}
	}
	return (files);
}

static void		set_args(t_list **list, t_ls_datas *ls_datas,
							t_file_datas *file, int file_type,
							const char *file_name)
{
	(void)file;
	if (*list)
	{
		(*list)->next = fetch_file_datas(ls_datas, file_name, "");
		//(*list)->next = ft_lstnew((void *)file, sizeof(t_file_datas));
		*list = (*list)->next;
	}
	else
	{
		*list = fetch_file_datas(ls_datas, file_name, "");
		//*list = ft_lstnew((void *)file, sizeof(t_file_datas));
		if (file_type == 0)
			ls_datas->directories = *list;
		else
			ls_datas->files = *list;
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
		ret = stat(file.name, &st_stat);
		if (ret < 0)
		{
			error_path(file.name);
			ft_strdel(&file.name);
		}
		else if (S_ISDIR(st_stat.st_mode))
			set_args(&dir_list, ls_datas, &file, 0, file.name);
		else if (S_ISREG(st_stat.st_mode))
			set_args(&files_list, ls_datas, &file, 1, file.name);
		else if (S_ISLNK(st_stat.st_mode))
			set_args(&files_list, ls_datas, &file, 2, file.name);
	}
	if (!ls_datas->directories && !files_list)
	{
		file.name = ft_strdup(".");
		ls_datas->directories = ft_lstnew((void *)&file, sizeof(t_file_datas));
	}
}

