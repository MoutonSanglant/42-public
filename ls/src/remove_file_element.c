/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_file_element.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:09:12 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/17 17:12:42 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		remove_file_element(void *element, size_t size)
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
