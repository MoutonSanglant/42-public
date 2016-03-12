/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 16:30:35 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/12 13:02:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	sort_antilexicographic (void *struct1, void *struct2)
{
	const char *s1;
	const char *s2;

	s1 = ((t_file_datas *)struct1)->name;
	s2 = ((t_file_datas *)struct2)->name;
	return (ft_strcmp(s1, s2) >= 0);
}

int	sort_lexicographic (void *struct1, void *struct2)
{
	const char *s1;
	const char *s2;

	s1 = ((t_file_datas *)struct1)->name;
	s2 = ((t_file_datas *)struct2)->name;
	return (ft_strcmp(s1, s2) <= 0);
}

int sort_time (void *struct1, void *struct2)
{
	time_t		t1;
	time_t		t2;
	int			ret;

	t1 = ((struct stat)((t_file_datas *)struct1)->st_stat).st_mtimespec.tv_sec;
	t2 = ((struct stat)((t_file_datas *)struct2)->st_stat).st_mtimespec.tv_sec;
	ret = (int)(t2 - t1) <= 0;
	if (!ret)
		return (sort_lexicographic(struct1, struct2));
	//if (!ret)
	return (ret);
}

int sort_time_reverse (void *struct1, void *struct2)
{
	time_t		t1;
	time_t		t2;
	int			ret;

	t1 = ((struct stat)((t_file_datas *)struct1)->st_stat).st_mtimespec.tv_sec;
	t2 = ((struct stat)((t_file_datas *)struct2)->st_stat).st_mtimespec.tv_sec;
	ret = (int)(t2 - t1) >= 0;
	if (!ret)
		return (sort_antilexicographic(struct1, struct2));
	return (ret);
}
