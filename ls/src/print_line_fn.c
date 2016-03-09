/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line_fn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 11:43:49 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/09 11:58:26 by tdefresn         ###   ########.fr       */
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

void	print_line(const t_file_datas *file_data)
{
	ft_printf("%s\n", file_data->file);
}
