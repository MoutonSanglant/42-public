/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 16:32:24 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/13 17:44:50 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*indent_str(char *dst, size_t len, int c, int reverse)
{
	char	*str;
	char	*tmp;
	size_t	i;
	size_t	n;

	tmp = dst;
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
	ft_strdel(&tmp);
	return (dst);
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
	username = getpwuid(st_stat->st_uid)->pw_name;
	username = indent_str(username, ls_datas->col_user_width, ' ', 0);
	groupname = getgrgid(st_stat->st_gid)->gr_name;
	groupname = indent_str(groupname, ls_datas->col_group_width, ' ', 0);
	ft_printf("%s %s %s  %s  ", mode_str, links_str, username, groupname);
	ft_strdel(&links_str);
}

static void		print_right(const t_ls_datas *ls_datas,
							const struct stat *st_stat, const char *filename)
{
	char	*size_str;
	char	*date;
	time_t	now;

	now = time(NULL);
	date = ctime(&st_stat->ST_MTIM.tv_sec);
	if (now - (time_t)st_stat->ST_MTIM.tv_sec > MONTH_IN_SECS * 6)
		ft_strcpy(&date[11], &date[19]);
	else if (-(now - (time_t)st_stat->ST_MTIM.tv_sec) > 0)
		ft_strcpy(&date[11], &date[19]);
	size_str = ft_uitoa((size_t)st_stat->st_size);
	size_str = indent_str(size_str, ls_datas->col_size_width, ' ', 1);
	ft_printf("%s %.12s %s\n", size_str, &date[4], filename);
	ft_strdel(&size_str);
}

void			print_detailed_line(const t_ls_datas *ls_datas,
										t_file_datas *file)
{
	const struct stat	*st_stat;
	char				*buf;
	char				*tmp;
	ssize_t				rbytes;

	buf = NULL;
	rbytes = 0;
	st_stat = &file->st_stat;
	if (S_ISLNK(st_stat->st_mode))
	{
		buf = ft_strnew(st_stat->st_size);
		if ((rbytes = readlink(file->pathname, buf, st_stat->st_size)))
		{
			buf[rbytes] = '\0';
			tmp = ft_strjoin(file->name, " -> ");
			ft_strdel(&file->name);
			file->name = ft_strjoin(tmp, buf);
			ft_strdel(&tmp);
		}
		ft_strdel(&buf);
	}
	print_left(ls_datas, st_stat);
	print_right(ls_datas, st_stat, file->name);
}

void			print_one(const t_ls_datas *ls_datas, const t_file_datas *file)
{
	(void)ls_datas;
	ft_printf("%s\n", file->name);
}
