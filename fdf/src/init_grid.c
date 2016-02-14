/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 20:00:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/14 12:59:57 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		clean_vertmap(t_vert **vertmap, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		ft_memdel((void **)&vertmap[i]);
		i++;
	}
	ft_memdel((void *)&vertmap);
}

void			init_grid(t_grid *grid, int width, int height)
{
	t_vert	**vertmap;
	t_vec2	ij;

	ij.x = 0;
	if (!(vertmap = (t_vert **)ft_memalloc(sizeof(t_vert *) * width)))
		alloc_error("vertmap", sizeof(t_vert *) * width);
	while (ij.x < width)
	{
		ij.y = 0;
		if (!(vertmap[ij.x] = (t_vert *)ft_memalloc(sizeof(t_vert) * height)))
			alloc_error("vertmap[i]", sizeof(t_vert) * height);
		while (ij.y < height)
		{
			vertmap[ij.x][ij.y].coord.x = ij.x;
			vertmap[ij.x][ij.y].coord.y = ij.y;
			vertmap[ij.x][ij.y].coord.z = 0.f;
			vertmap[ij.x][ij.y].color.r = 0.f;
			vertmap[ij.x][ij.y].color.g = 1.f;
			vertmap[ij.x][ij.y].color.b = 0.7f;
			ij.y++;
		}
		ij.x++;
	}
	init_grid_from_vertmap(grid, vertmap, width - 1, height - 1);
	clean_vertmap(vertmap, height);
}
