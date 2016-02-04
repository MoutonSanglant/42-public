/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 20:00:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 02:27:41 by tdefresn         ###   ########.fr       */
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
	int		i;
	int		j;

	i = 0;
	vertmap = (t_vert **)ft_memalloc(sizeof(t_vert *) * width);
	while (i < width)
	{
		j = 0;
		vertmap[i] = (t_vert *)ft_memalloc(sizeof(t_vert) * height);
		while (j < height)
		{
			vertmap[i][j].coord.x = i;
			vertmap[i][j].coord.y = j;
			vertmap[i][j].coord.z = 0;
			vertmap[i][j].color.r = 0;
			vertmap[i][j].color.g = 0;
			vertmap[i][j].color.b = 0;
			j++;
		}
		i++;
	}
	init_grid_from_vertmap(grid, vertmap, width, height);
	clean_vertmap(vertmap, height);
}
