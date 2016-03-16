/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 17:07:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/16 01:11:56 by tdefresn         ###   ########.fr       */
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
			ls_datas->print_fn = &print_detailed_line;
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
			if (argv[i][2] == '-')
				error_usage('-', ls_datas);
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
								t_list **list, int is_dir)
{
	if (*list)
	{
		(*list)->next =
			(is_dir) ? ft_lstnew((void *)file, sizeof(t_file_datas))
			: fetch_file_datas(ls_datas, file, "");
		*list = (*list)->next;
	}
	else
	{
		if (is_dir)
		{
			*list = ft_lstnew((void *)file, sizeof(t_file_datas));
			ls_datas->directories = *list;
		}
		else
		{
			*list = fetch_file_datas(ls_datas, file, "");
			ls_datas->files = *list;
		}
	}
}

/*
**	Bon, de nouveaux bug avec le test S_ISLNK (fonctionnel ?)
**	Regarder les tests du Moulitest...
**	+ LA NORME !
*/

void			fetch_args(int argc, char **argv, t_ls_datas *ls_datas)
{
	t_list			*dir_list;
	t_list			*files_list;
	t_file_datas	file;
	struct stat		st_stat;
	int				flag_count;
	DIR				*p_dir;

	dir_list = NULL;
	files_list = NULL;
	flag_count = fetch_flags(argc, argv, ls_datas);
	while (--argc > flag_count)
	{
		file.pathname = NULL;
		file.name = ft_strdup(argv[argc]);
		lstat(file.name, &st_stat);
		if (S_ISREG(st_stat.st_mode))
			add_file(ls_datas, &file, &files_list, 1);
		else if (S_ISLNK(st_stat.st_mode))
		{
			if (!(p_dir = opendir(file.name)))
				add_file(ls_datas, &file, &files_list, 0);
			else
			{
				add_file(ls_datas, &file, &dir_list, 1);
				closedir(p_dir);
			}
		}
		else
			add_file(ls_datas, &file, &dir_list, 1);
	}
	if (!ls_datas->directories && !files_list)
	{
		file.name = ft_strdup(".");
		file.pathname = NULL;
		add_file(ls_datas, &file, &dir_list, 1);
	}
}
