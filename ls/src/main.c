/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 17:43:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/08 01:15:32 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	ls params:
**	-l		List			List in long format (show files details)
**	-R		Recusive		Recursively list subdirectories encountered
**	-a		Hidden files	Print entries beginning with a '.'
**	-r		Reverse			Print in reverse order (lexi or creation)
**	-t		Sort: time		Sort by modification time (recent first) then lexi
**	=============
**	no ACL
**	-l & -R first
**	=============
**	Authorized functions:
**		write
**		>> opendir (errno)
**		>> readdir
**		>> closedir
**		>> stat
**		>> lstat
**		>> getpwuid
**		>> getgrgid
**		>> listxattr
**		>> getxattr
**		time
**		>> ctime
**		>> readlink
**		malloc
**		free
**		perror
**		strerror
**		exit
*/

/*
**	2 steps routine:
**	- read flags
**	- read paths
*/

//void	print_detailed_line(const char *str)
void	print_detailed_line(const t_file_datas *file_data)
{
	ft_printf("-rwxrwxrwx  1 tdefresn  2015_paris %6i Mar %2i 25:99 %s\n", (size_t)file_data->stat.st_size, 0, file_data->file);
			//ft_printf("%i: %i\n", ret, (size_t)f_stat.st_size);
}

//void	print_line(const char *str)
void	print_line(const t_file_datas *file_data)
{
	ft_printf("%s\n", file_data->file);
}

static int	sort_antilexicographic (void *s1, void *s2)
{
	return (ft_strcmp((const char *)s1, (const char *)s2) > 0);
}

static int	sort_lexicographic (void *s1, void *s2)
{
	return (ft_strcmp((const char *)s1, (const char *)s2) <= 0);
}

/*
**	Should set a function pointer to a specific print method
*/

static int		read_flags(int argc, char **argv, t_ls_datas *ls_datas)
{
	int		i;
	int		j;
	int		len;
	char	*arg;

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
				ls_datas->flags |= FLAG_L;
			else if (arg[j] == 'r')
				ls_datas->flags |= FLAG_R;
			else if (arg[j] == 't')
				ls_datas->flags |= FLAG_T;
			else
				error_usage(arg[j]);
		}
	}
	return (i - 1);
}

static void		read_args(int argc, char **argv, t_ls_datas *ls_datas)
{
	t_list	*path;
	char	*tmp;
	char	*arg;
	int		i;

	path = NULL;
	i = read_flags(argc, argv, ls_datas);
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

/*
**	Degueulasse...
**	A reecrire, ainsi que ft_lstsort ! :)
*/
int		read_dir(t_list *path, t_ls_flags flags,
					void (*print_fn)(const t_file_datas *),
					int (*sort_fn)(void *, void *))
{
	struct dirent	*p_dirent;
	DIR				*p_dir;
	char			*d_name;
	t_list			*list;
	t_list			*list_start;
	t_file_datas	file_data;
	t_file_datas	*p_file_data;
	int				ret;

	list = NULL;
	list_start = NULL;
	p_dir = opendir((char *)path->content);
	if (!p_dir)
		return (error_path((char *)path->content));
	if (((char *)path->content)[0] != '.')
		ft_printf("%s: \n", (char *)path->content);
	while ((p_dirent = readdir(p_dir)))
	{
		d_name = p_dirent->d_name;
		if (!list)
		{
			if (d_name[0] != '.' || flags & FLAG_A)
			{
				file_data.file = d_name;
				ret = stat(d_name, &file_data.stat);
				if (ret < 0)
					error_unimplemented();
				list = ft_lstnew((void *)&file_data, sizeof(t_file_datas));
			}
				//list = ft_lstnew((void *)d_name, sizeof(char) * (ft_strlen(d_name) + 1));
		}
		else
		{
			if (d_name[0] != '.' || flags & FLAG_A)
			{
				file_data.file = d_name;
				ret = stat(d_name, &file_data.stat);
				if (ret < 0)
					error_unimplemented();
				list->next = ft_lstnew((void *)&file_data, sizeof(t_file_datas));
				//list->next = ft_lstnew((void *)d_name, sizeof(char) * (ft_strlen(d_name) + 1));
				list = list->next;
			}
		}
		if (!list_start)
			list_start = list;
	}
	if (list)
		list = ft_lstsort(list_start, sort_fn);
	while (list)
	{
		p_file_data = (t_file_datas *)list->content;
		print_fn(p_file_data);
		list = list->next;
		/*
		**	Memory is not freed yet (should use lstdel)
		*/
	}
	closedir(p_dir);
	return (0);
}

int		main(int argc, char **argv)
{
	t_ls_datas		ls_datas;
	t_list			*path;
	int				error;
	int				last_error;
	void			(*print)(const t_file_datas *);
	int				(*sort)(void *, void *);

	ls_datas.flags = FLAG_NONE;
	ls_datas.path = NULL;

	error = 0;
	read_args(argc, argv, &ls_datas);
	path = ls_datas.path;
	print = &print_line;
	sort = &sort_lexicographic;
	if (ls_datas.flags & FLAG_L)
		print = &print_detailed_line;
	if (ls_datas.flags & FLAG_R)
		sort = &sort_antilexicographic;
	while (path)
	{
		path = ft_lstsort(path, &sort_lexicographic);
		last_error = read_dir(path, ls_datas.flags, print, sort);
		if (last_error)
			error = last_error;
		path = path->next;
	}
	return (error);
}
