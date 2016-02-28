/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   human_play_turn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/28 11:41:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/28 11:43:46 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puissance4.h"

int		human_play_turn(t_grid *game)
{
	char	*buf;
	int		check;
	int		i;

	check = 0;
	while (check == 0)
	{
		ft_putendl("Please enter a valid column number : ");
		i = 0;
		get_next_line(0, &buf);
		if (buf[0] && ft_atoi(buf) <= game->col &&
				game->grid[0][ft_atoi(buf)] == '.')
		{
			check = 1;
			while (buf[i])
			{
				if (!ft_isdigit(buf[i]))
					check = 0;
				i++;
			}
		}
	}
	return (ft_atoi(buf));
}
