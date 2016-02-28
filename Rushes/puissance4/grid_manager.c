/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 18:33:42 by gdruel            #+#    #+#             */
/*   Updated: 2016/02/28 13:07:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puissance4.h"

static void		put_colored_char(t_grid *game, char c)
{
	ft_putchar('|');
	if (c != '.')
	{
		if (c == game->player->token)
			ft_putstr(game->player->color);
		else
			ft_putstr(game->player->other->color);
	}
	ft_putchar(c);
	ft_putstr("\x1B[0m");
}

void			destroy_game(t_grid *game, int lines)
{
	int		i;

	i = 0;
	while (i < lines)
	{
		ft_memdel((void **)&game->grid[i]);
		i++;
	}
	ft_memdel((void **)&game->grid);
	ft_memdel((void **)&game);
}

/*
**	Function is hijacking 'game' state field
*/

void			place(int col, t_grid *game, int id)
{
	int		i;

	i = game->lin - 1;
	while (i >= 0 && game->grid[i][col] != '.')
		i--;
	if (id == 1)
		game->grid[i][col] = AI_TOKEN;
	else
		game->grid[i][col] = PLAYER_TOKEN;
	display_grid(game);
	check_victory(game);
}

void			display_grid(t_grid *game)
{
	int		i;
	int		j;

	j = 0;
	while (j < game->lin)
	{
		i = 0;
		while (i < game->col)
			put_colored_char(game, game->grid[j][i++]);
		ft_putendl("|");
		j++;
	}
	j = 0;
	while (j < game->col)
	{
		ft_putchar('|');
		ft_putnbr(j % 10);
		j++;
	}
	ft_putendl("| \n");
}

t_grid			*init(t_grid *game, int lines, int columns)
{
	int		i;
	int		j;

	i = 0;
	game->grid = (char**)ft_memalloc(sizeof(char *) * (lines + 1));
	game->grid[lines] = NULL;
	while (i < lines)
	{
		j = 0;
		game->grid[i] = (char *)ft_memalloc(sizeof(char) * (columns + 1));
		while (j < columns)
		{
			game->grid[i][j] = '.';
			j++;
		}
		game->grid[i][columns] = '\0';
		i++;
	}
	game->lin = lines;
	game->col = columns;
	game->state = 0;
	return (game);
}
