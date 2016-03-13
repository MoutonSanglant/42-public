/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 16:30:35 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/13 15:28:09 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_antilexicographic(void *struct1, void *struct2)
{
	const char *s1;
	const char *s2;

	s1 = ((t_file_datas *)struct1)->name;
	s2 = ((t_file_datas *)struct2)->name;
	return (ft_strcmp(s1, s2) >= 0);
}

int		sort_lexicographic(void *struct1, void *struct2)
{
	const char *s1;
	const char *s2;

	s1 = ((t_file_datas *)struct1)->name;
	s2 = ((t_file_datas *)struct2)->name;
	return (ft_strcmp(s1, s2) <= 0);
}

int		sort_time(void *struct1, void *struct2)
{
	struct timespec		t1;
	struct timespec		t2;

	t1 = ((struct stat)((t_file_datas *)struct1)->st_stat).ST_MTIM;
	t2 = ((struct stat)((t_file_datas *)struct2)->st_stat).ST_MTIM;
	if (t1.tv_sec == t2.tv_sec)
	{
		if (t1.tv_nsec == t2.tv_nsec)
			return (sort_lexicographic(struct1, struct2));
		return ((int)(t2.tv_nsec - t1.tv_nsec) <= 0);
	}
	return ((int)(t2.tv_sec - t1.tv_sec) <= 0);
}

int		sort_time_reverse(void *struct1, void *struct2)
{
	struct timespec		t1;
	struct timespec		t2;

	t1 = ((struct stat)((t_file_datas *)struct1)->st_stat).ST_MTIM;
	t2 = ((struct stat)((t_file_datas *)struct2)->st_stat).ST_MTIM;
	if (t1.tv_sec == t2.tv_sec)
	{
		if (t1.tv_nsec == t2.tv_nsec)
			return (sort_antilexicographic(struct1, struct2));
		return ((int)(t2.tv_nsec - t1.tv_nsec) >= 0);
	}
	return ((int)(t2.tv_sec - t1.tv_sec) >= 0);
}
