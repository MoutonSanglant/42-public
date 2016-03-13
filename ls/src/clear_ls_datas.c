/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_ls_datas.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 15:37:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/13 17:38:41 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		remove_element(void *element, size_t size)
{
	t_file_datas	*fdatas;

	(void)size;
	fdatas = (t_file_datas *)element;
	if (fdatas->name)
		ft_strdel(&fdatas->name);
	if (fdatas->pathname)
		ft_strdel(&fdatas->pathname);
	ft_memdel((void **)&element);
}

void	clear_ls_datas(t_ls_datas *ls_datas)
{
	if (ls_datas)
	{
		if (ls_datas->directories)
			ft_lstdel(&ls_datas->directories, &remove_element);
		if (ls_datas->files)
			ft_lstdel(&ls_datas->files, &remove_element);
	}
}
