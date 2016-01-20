/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 20:00:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/19 16:15:46 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_grid(t_vector3 *grid)
{
	int		x;
	int		y;
	x = 0;
	y = 0;
	while (x < 10)
	{
		while(y < 10)
		{
			grid[x + y * 10].x = (double)(50.f * x);
			grid[x + y * 10].y = (double)(50.f * y);
			//grid[x + y * 10].z = (double)(50 * y);
			//grid[x + y * 10].y = 0.0;
			grid[x + y * 10].z = 0.f;
			y++;
		}
		y = 0;
		x++;
	}
}
