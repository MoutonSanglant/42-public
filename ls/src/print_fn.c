/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 16:32:24 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/14 21:23:13 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*indent_str(char *dst, size_t len, int c, int reverse)
{
	char	*str;
	char	*new_dst;
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
	new_dst = (reverse) ? ft_strjoin(str, dst) : ft_strjoin(dst, str);
	ft_strdel(&dst);
	ft_strdel(&str);
	return (new_dst);
}

static void		print_left(const t_ls_datas *ls_datas,
							const struct stat *st_stat)
{
	char	mode_str[12];
	char	*links_str;
	char	*username;
	char	*groupname;

	file_mode_str(st_stat->st_mode, mode_str);
	links_str = ft_uitoa((unsigned)st_stat->st_nlink);
	links_str = indent_str(links_str, ls_datas->col_links_width, ' ', 1);
	username = ft_strdup(getpwuid(st_stat->st_uid)->pw_name);
	username = indent_str(username, ls_datas->col_user_width, ' ', 0);
	groupname = ft_strdup(getgrgid(st_stat->st_gid)->gr_name);
	groupname = indent_str(groupname, ls_datas->col_group_width, ' ', 0);
	ft_printf("%s %s %s  %s  ", mode_str, links_str, username, groupname);
	ft_strdel(&links_str);
	ft_strdel(&groupname);
	ft_strdel(&username);
}

static void		print_right(const t_ls_datas *ls_datas,
							const struct stat *st_stat, const char *filename)
{
	char	*maj_col;
	char	*min_col;
	char	*date;
	time_t	now;

	min_col = NULL;
	now = time(NULL);
	date = ctime(&st_stat->ST_MTIM.tv_sec);
	if (now - (time_t)st_stat->ST_MTIM.tv_sec > MONTH_IN_SECS * 6 ||
			-(now - (time_t)st_stat->ST_MTIM.tv_sec) > 0)
		ft_strcpy(&date[11], &date[19]);
	if (S_ISCHR(st_stat->st_mode) || S_ISBLK(st_stat->st_mode))
	{
		maj_col = indent_str(ft_itoa(MAJOR(st_stat->st_rdev)), 3, ' ', 1);
		min_col = indent_str(ft_itoa(MINOR(st_stat->st_rdev)), 3, ' ', 1);
		ft_printf("%s, %s %.12s %s\n", maj_col, min_col, &date[4], filename);
		ft_strdel(&maj_col);
	}
	else
	{
		min_col = indent_str(ft_uitoa((size_t)st_stat->st_size),
								ls_datas->col_size_width, ' ', 1);
		ft_printf("%s %.12s %s\n", min_col, &date[4], filename);
	}
	ft_strdel(&min_col);
}

void			print_detailed_line(const t_ls_datas *ls_datas,
										t_file_datas *file)
{
	const struct stat	*st_stat;
	char				*tmp;
	char				*filename;
	char				buf[1024];
	ssize_t				rbytes;

	rbytes = 0;
	st_stat = &file->st_stat;
	if (S_ISLNK(st_stat->st_mode))
	{
		if ((rbytes = readlink(file->pathname, buf, sizeof(buf) - 1)) != -1)
			buf[rbytes] = '\0';
		tmp = ft_strjoin(file->name, " -> ");
		filename = ft_strjoin(tmp, buf);
		ft_strdel(&tmp);
	}
	else
		filename = ft_strdup(file->name);
	print_left(ls_datas, st_stat);
	print_right(ls_datas, st_stat, filename);
	ft_strdel(&filename);
}

void			print_one(const t_ls_datas *ls_datas, t_file_datas *file)
{
	(void)ls_datas;
	ft_printf("%s\n", file->name);
}
