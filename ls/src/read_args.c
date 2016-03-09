/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 11:45:42 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/09 12:02:41 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	sort_antilexicographic (void *struct1, void *struct2)
{
	const char *s1;
	const char *s2;

	s1 = ((t_file_datas *)struct1)->file;
	s2 = ((t_file_datas *)struct2)->file;
	return (ft_strcmp(s1, s2) > 0);
}

static int	sort_lexicographic (void *struct1, void *struct2)
{
	const char *s1;
	const char *s2;

	s1 = ((t_file_datas *)struct1)->file;
	s2 = ((t_file_datas *)struct2)->file;
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
	t_list	*path;
	char	*tmp;
	char	*arg;
	int		i;

	path = NULL;
	i = fetch_flags(argc, argv, ls_datas);
	while (++i < argc)
	{
		arg = argv[i];
		if ((tmp = ft_strdup(arg)))
		{
			if (path)
			{
				path->next = ft_lstnew((void *)tmp, sizeof(char) * (ft_strlen(tmp) + 1));
				path = path->next;
			}
			else
				path = ft_lstnew((void *)tmp, sizeof(char) * (ft_strlen(tmp) + 1));
			if (!ls_datas->path)
				ls_datas->path = path;
			ft_strdel(&tmp);
		}
	}
	if (!ls_datas->path)
		ls_datas->path = ft_lstnew((void *)".", sizeof(char) * 2);
}

