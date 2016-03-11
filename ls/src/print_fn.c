/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 16:32:24 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/11 14:49:07 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	else if (S_ISLNK(mode))
		str[0] = 'l';
	else if (S_ISCHR(mode))
		str[0] = 'c';
	else if (S_ISBLK(mode))
		str[0] = 'b';
	else if (S_ISFIFO(mode))
		str[0] = 'p';
	else if (S_ISSOCK(mode))
		str[0] = 's';
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

char	*indent_str(char *dst, size_t len, int c, int reverse)
{
	char	*str;
	size_t	i;
	size_t	n;

	n = len - ft_strlen(dst);
	if (n <= 0)
		return (dst);

	i = 0;
	str = ft_strnew(n);
	while (i < n)
		str[i++] = c;
	str[i] = '\0';
	dst = (reverse) ? ft_strjoin(str, dst) : ft_strjoin(dst, str);
	ft_strdel(&str);
	return (dst);
}

/*
** - Not printing the correct number after 'total' (look in upward function)
*/

#ifdef _DARWIN_FEATURE_64_BIT_INODE
void	print_detailed_line(const t_ls_datas *ls_datas, const t_file_datas *file)
{
	char				*username;
	char				*groupname;
	char				*str_links;
	char				*str_size;
	char				mode_str[12];
	char				*date;
	const struct stat	*st_stat;
	char				*lnk;
	char				*buf;
	ssize_t					rbytes;
	time_t					now;

	rbytes = 0;
	buf = NULL;
	lnk = NULL;
	st_stat = &file->st_stat;
	if (S_ISLNK(st_stat->st_mode))
	{
		buf = ft_strnew(st_stat->st_size);
		if ((rbytes = readlink(file->pathname, buf, st_stat->st_size)))
		{
			buf[rbytes] = '\0';
			lnk = ft_strjoin(" -> ", buf);
		}
		ft_strdel(&buf);
	}
	else
		lnk = ft_strdup("");
	now = time(NULL);
	date = ctime(&st_stat->st_mtimespec.tv_sec);
	if (now - (time_t)st_stat->st_mtimespec.tv_sec > MONTH_IN_SECS * 6)
		ft_strcpy(&date[11], &date[19]);
	else if (-(now - (time_t)st_stat->st_mtimespec.tv_sec) > 0)
		ft_strcpy(&date[11], &date[19]);
	file_mode_to_str(st_stat->st_mode, mode_str);
	username = getpwuid(st_stat->st_uid)->pw_name;
	groupname = getgrgid(st_stat->st_gid)->gr_name;
	username = indent_str(username, ls_datas->col_user_width, ' ', 0);
	groupname = indent_str(groupname, ls_datas->col_group_width, ' ', 0);
	str_links = ft_uitoa((unsigned)st_stat->st_nlink);
	str_links = indent_str(str_links, ls_datas->col_links_width, ' ', 1);
	str_size = ft_uitoa((size_t)st_stat->st_size);
	str_size = indent_str(str_size, ls_datas->col_size_width, ' ', 1);
	/*
	**	The user & group columns need to know the biggest entry
	**	to compute the correct padding
	*/
	ft_printf("%s %s %s  %s  %s %.12s %s%s\n", mode_str, str_links, username,
			groupname, str_size, &date[4], file->name, lnk);
	ft_strdel(&str_links);
	ft_strdel(&str_size);
	ft_strdel(&lnk);
	/*
	ft_memdel((void **)&file_passwd);
	ft_memdel((void **)&file_group);
	ft_strdel(&date);
	*/
}
#else
void	print_detailed_line(const t_ls_datas *ls_datas, const t_file_datas *file)
{
	struct passwd		*file_passwd;
	struct group		*file_group;
	char				mode_str[12];
	char				*date;
	const struct stat	*st_stat;

	(void)ls_datas;
	st_stat = &file->st_stat;
	//ft_printf("Darwin 64\n");
	date = ctime(&st_stat->st_mtim.tv_sec);
	file_mode_to_str(st_stat->st_mode, mode_str);
	file_passwd = getpwuid(st_stat->st_uid);
	file_group = getgrgid(st_stat->st_gid);
	/*
	**	The user & group columns need to know the biggest entry
	**	to compute the correct padding
	*/
	ft_printf("%s %2i %-12.12s  %-12.12s %6i %.12s %s\n", mode_str, (unsigned)st_stat->st_nlink, file_passwd->pw_name, file_group->gr_name, (size_t)st_stat->st_size, &date[4], file->name);
	/*
	ft_memdel((void **)&file_passwd);
	ft_memdel((void **)&file_group);
	ft_strdel(&date);
	*/
}

#endif

void	print_one(const t_ls_datas *ls_datas, const t_file_datas *file)
{
	(void)ls_datas;
	ft_printf("%s\n", file->name);
}
