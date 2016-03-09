/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 11:45:42 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/09 14:08:37 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	sort_antilexicographic (void *struct1, void *struct2)
{
	const char *s1;
	const char *s2;

	s1 = ((t_file_datas *)struct1)->name;
	s2 = ((t_file_datas *)struct2)->name;
	return (ft_strcmp(s1, s2) > 0);
}

static int	sort_lexicographic (void *struct1, void *struct2)
{
	const char *s1;
	const char *s2;

	s1 = ((t_file_datas *)struct1)->name;
	s2 = ((t_file_datas *)struct2)->name;
	return (ft_strcmp(s1, s2) <= 0);
}

static int		fetch_flags(int argc, char **argv, t_ls_datas *ls_datas)
{
	char	*arg;
	int		len;
	int		i;
	int		j;
	int		reverse;

	reverse = 0;
	ls_datas->print_fn = &print_line;
	ls_datas->sort_fn = &sort_lexicographic;
	i = 0;
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

void			read_args(int argc, char **argv, t_ls_datas *ls_datas)
{
	t_list	*folder_list;
	t_file_datas	folder;
	char	*tmp;
	char	*arg;
	int		i;

	folder_list = NULL;
	i = fetch_flags(argc, argv, ls_datas);
	while (++i < argc)
	{
		arg = argv[i];
		if ((tmp = ft_strdup(arg)))
		{
			if (folder_list)
			{
				folder.name = ft_strdup(tmp);
				//folder.st_stat = NULL;
				folder_list->next = ft_lstnew((void *)&folder, sizeof(t_file_datas));
				folder_list = folder_list->next;
			}
			else
			{
				folder.name = ft_strdup(tmp);
				//folder.st_stat = NULL;
				folder_list = ft_lstnew((void *)&folder, sizeof(t_file_datas));
				if (!ls_datas->folders)
					ls_datas->folders = folder_list;
			}
			ft_strdel(&tmp);
		}
	}
	if (!ls_datas->folders)
	{
		folder.name = ft_strdup(".");
		//folder.st_stat = NULL;
		ls_datas->folders = ft_lstnew((void *)&folder, sizeof(t_file_datas));
	}
}

