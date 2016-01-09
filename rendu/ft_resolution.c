/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuchwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 15:55:31 by mabuchwa          #+#    #+#             */
/*   Updated: 2016/01/09 16:28:17 by mabuchwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void			ft_print_board(char **board, int side)
{
	int		i;

	i = 0;
	while (i < side)
	{
		ft_putstr(board[i]);
		i++;
	}
}

static void		ft_clear_board(char **board, char c)
{
	int		i;
	int		j;

	i = 0;
	while (board[i] != 0)
	{
		j = 0;
		while (board[i][j] != '\0')
		{
			if (board[i][j] == c)
				board[i][j] = '.';
			j++;
		}
		i++;
	}
}

static void		ft_insert_char(char **board, t_pos *tab, int box, t_val value)
{
	int		block;
	int		b;
	int		a;
	int		tmp_a;
	int		tmp_b;

	block = 0;
	b = box % value.sd;
	a = box / value.sd;
	tmp_a = a;
	tmp_b = b;
	while (block < 4)
	{
		board[a][b] = (tab + value.n_tetri)->letter;
		block++;
		a = tmp_a + ((tab + value.n_tetri)->y[block]
				- (tab + value.n_tetri)->y[0]);
		b = tmp_b + ((tab + value.n_tetri)->x[block]
				- (tab + value.n_tetri)->x[0]);
	}
}

static int		ft_test(char **board, t_pos *tab, int box, t_val value)
{
	int		block;
	int		b;
	int		a;
	int		tmp_a;
	int		tmp_b;

	block = 0;
	b = box % value.sd;
	a = box / value.sd;
	tmp_a = a;
	tmp_b = b;
	while (block < 4)
	{
		if (a < value.sd && b < value.sd && board[a][b] == '.')
		{
			block++;
			a = tmp_a + (TAB->y[block] - TAB->y[0]);
			b = tmp_b + (TAB->x[block] - TAB->x[0]);
		}
		else
			return (1);
	}
	ft_insert_char(board, tab, box, value);
	return (0);
}

void			ft_resolution(char **board, int side, t_pos *tab, int num_tetri)
{
	int		box;
	int		box_max;
	t_val	value;

	box = 0;
	box_max = side * side;
	value.sd = side;
	value.n_tetri = num_tetri;
	if (num_tetri == tab->nb_tetri)
	{
		ft_print_board(board, side);
		exit(0);
	}
	while (num_tetri < tab->nb_tetri && box < box_max)
	{
		if (ft_test(board, tab, box, value) == 0)
			ft_resolution(board, side, tab, num_tetri + 1);
		box++;
	}
	if (box == box_max && num_tetri != 0)
		ft_clear_board(board, (tab + (value.n_tetri - 1))->letter);
	if (box == box_max && num_tetri == 0)
		ft_get_size(board, tab, side + 1);
}
