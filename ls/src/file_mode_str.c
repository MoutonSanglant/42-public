/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mode_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 11:26:55 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/14 14:07:41 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		set_owner_group_user(mode_t mode, char *str)
{
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

static void		set_special_flags(mode_t mode, char *str)
{
	if (S_ISBLK(mode))
		str[0] = 'b';
	else if (mode & S_IFDIR)
		str[0] = 'd';
	else if (S_ISFIFO(mode))
		str[0] = 'p';
	else if (S_ISSOCK(mode))
		str[0] = 's';
	else if (S_ISLNK(mode))
		str[0] = 'l';
	else if (S_ISCHR(mode))
		str[0] = 'c';
}

void			file_mode_str(mode_t mode, char *str)
{
	int		i;

	i = 0;
	while (i < 11)
		str[i++] = '-';
	str[10] = ' ';
	str[11] = '\0';
	set_special_flags(mode, str);
	set_owner_group_user(mode, str);
}
