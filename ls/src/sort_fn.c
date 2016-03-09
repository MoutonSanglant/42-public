/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 16:30:35 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/09 19:59:28 by tdefresn         ###   ########.fr       */
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
