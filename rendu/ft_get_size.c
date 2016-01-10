/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuchwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 15:56:48 by mabuchwa          #+#    #+#             */
/*   Updated: 2016/01/09 16:54:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void		ft_free_board(char **board, int side)
{
	int		i;

	i = 0;
	while (i < side - 1)
	{
		free(board[i]);
		board[i] = NULL;
		i++;
	}
	free(board);
	board = NULL;
}

static char		**ft_get_board(int side)
{
	char	**board;
	int		i;

	i = 0;
	if (!(board = (char**)malloc(sizeof(*board) * side + 1)))
		return (NULL);
	board[side] = 0;
	while (i < side)
	{
		if (!(board[i] = (char*)malloc(sizeof(**board) * (side + 1))))
			return (NULL);
		ft_memset(board[i], '.', side);
		board[i][side] = '\0';
		i++;
	}
	return (board);
}

void			ft_get_size(char **board, t_pos *tab, int side)
{
	int		size;
	int		tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = (tab + i)->nb_tetri * 4;
	if (side == 0)
	{
		while ((side * side) < size)
		{
			tmp = (side * side);
			side++;
		}
	}
	if (board != NULL)
		ft_free_board(board, side);
	board = ft_get_board(side);
	ft_resolution(board, side, tab, 0);
}
