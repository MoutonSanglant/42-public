/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 17:43:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/08 20:35:03 by tdefresn         ###   ########.fr       */
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
**		*>> opendir (errno)
**		*>> readdir
**		*>> closedir
**		*>> stat
**		>> lstat // for symbolic links
**		*>> getpwuid
**		*>> getgrgid
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

static void		file_mode_to_str(mode_t mode, char *str)
{
	int		i;

	i = 0;
	while (i < 11)
		str[i++] = '-';
	str[10] = ' ';
	str[11] = '\0';
	if (mode & S_IFDIR)
		str[0] = 'd';
	if (mode & S_IRUSR)
		str[1] = 'r';
	if (mode & S_IWUSR)
		str[2] = 'w';
	if (mode & S_IXUSR)
		str[3] = 'x';
	if (mode & S_IRGRP)
		str[4] = 'r';
	if (mode & S_IWGRP)
		str[5] = 'w';
	if (mode & S_IXGRP)
		str[6] = 'x';
	if (mode & S_IROTH)
		str[7] = 'r';
	if (mode & S_IWOTH)
		str[8] = 'w';
	if (mode & S_IXOTH)
		str[9] = 'x';
}

//void	print_detailed_line(const char *str)
#ifdef _DARWIN_FEATURE_64_BIT_INODE
void	print_detailed_line(const t_file_datas *file_data)
{
	struct passwd	*file_passwd;
	struct group	*file_group;
	char			mode_str[12];
	char			*date;

	//ft_printf("Darwin 64\n");
	date = ctime(&file_data->st_stat.st_mtimespec.tv_sec);
	file_mode_to_str(file_data->st_stat.st_mode, mode_str);
	file_passwd = getpwuid(file_data->st_stat.st_uid);
	file_group = getgrgid(file_data->st_stat.st_gid);
	/*
	**	The user & group columns need to know the biggest entry
	**	to compute the correct padding
	*/
	ft_printf("%s %2i %-12.12s  %-12.12s %6i %.12s %s\n", mode_str, (unsigned)file_data->st_stat.st_nlink, file_passwd->pw_name, file_group->gr_name, (size_t)file_data->st_stat.st_size, &date[4], file_data->file);
	/*
	ft_memdel((void **)&file_passwd);
	ft_memdel((void **)&file_group);
	ft_strdel(&date);
	*/
}
#else
#endif

//void	print_line(const char *str)
void	print_line(const t_file_datas *file_data)
{
	ft_printf("%s\n", file_data->file);
}

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

static void		clear_file_list(void *node, size_t size)
{
	t_file_datas *file_data;

	(void) size;
	file_data = (t_file_datas *)node;
	//ft_printf("abc: %s\n", file_data->file);
	ft_memdel((void **)&file_data);
	//ft_memdel(&node);
}

static void		clear_path_list(void *node, size_t size)
{
	char	*str;

	(void)size;
	str = (char *)node;
	ft_strdel(&str);
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
	char			*full_path;
	char			*tmp;
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
	// Should output only when multiple folders
	// are inputed
//	if (((char *)path->content)[0] != '.')
//		ft_printf("%s: \n", (char *)path->content);
	while ((p_dirent = readdir(p_dir)))
	{
		d_name = p_dirent->d_name;
		if (!list)
		{
			if (d_name[0] != '.' || flags & FLAG_A)
			{
				file_data.file = d_name;
				// Prefix is missing, so we can't read subfolders until we
				// specify the whole path from the current directory
				full_path = ft_strjoin((char *)path->content, "/");
				tmp = full_path;
				full_path = ft_strjoin(full_path, d_name);
				ret = stat(full_path, &file_data.st_stat);
				if (ret < 0)
					error_unimplemented();
				list = ft_lstnew((void *)&file_data, sizeof(t_file_datas));
				ft_strdel(&tmp);
				ft_strdel(&full_path);
			}
				//list = ft_lstnew((void *)d_name, sizeof(char) * (ft_strlen(d_name) + 1));
		}
		else
		{
			if (d_name[0] != '.' || flags & FLAG_A)
			{
				file_data.file = d_name;
				// Prefix is missing, so we can't read subfolders until we
				// specify the whole path from the current directory
				full_path = ft_strjoin((char *)path->content, "/");
				tmp = full_path;
				full_path = ft_strjoin(full_path, d_name);
				ret = stat(full_path, &file_data.st_stat);
				//ret = stat(d_name, &file_data.stat);
				if (ret < 0)
					error_unimplemented();
				list->next = ft_lstnew((void *)&file_data, sizeof(t_file_datas));
				//list->next = ft_lstnew((void *)d_name, sizeof(char) * (ft_strlen(d_name) + 1));
				list = list->next;
				ft_strdel(&tmp);
				ft_strdel(&full_path);
			}
		}
		if (!list_start)
			list_start = list;
	}
	if (list)
		list = ft_lstsort(list_start, sort_fn);
	list_start = list;
	while (list)
	{
		p_file_data = (t_file_datas *)list->content;
		print_fn(p_file_data);
		list = list->next;
		/*
		**	Memory is not freed yet (should use lstdel)
		*/
	}
	ft_lstdel(&list_start, &clear_file_list);
	closedir(p_dir);
	return (0);
}

int		main(int argc, char **argv)
{
	t_ls_datas		ls_datas;
	t_list			*path;
	t_list			*prev;
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
		prev = path;
		path = path->next;
		ft_lstdelone(&prev, &clear_path_list);
	}
	return (error);
}
