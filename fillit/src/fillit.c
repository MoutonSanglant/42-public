/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 17:05:24 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/13 22:33:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_grid(unsigned long long int grid, int w)
{
	int i;
	unsigned long long int a;

	a = 1;
	i = 0;
	while (a)
	{
		if (i % w == 0)
		{
			ft_putchar('\n');
			if (i / w >= w)
				break;
		}

		if (grid & a)
		{
			ft_putchar('#');
		}
		else
			ft_putchar('.');

		i++;
		a = a << 1;
	}
	ft_putchar('\n');
}

int	biggest_square(int n)
{
	int	i;

	i = 0;
	while (i * i < n)
		i++;

	return (i);
}

unsigned long long int	convert_to(unsigned long long int n, int w)
{
	int i;
	int h;
	unsigned long long r;
	unsigned long long tmp;
	int d;

	d = w - 4;
	i = 0;
	h = 0;
	r = 0;
	while (i < 16)
	{
		if (i > 0 && i % 4 == 0)
			h++;
		tmp = n & (1 << i);
		if (tmp)
			r += tmp << h * d;
	//		r += tmp << h;
		i++;
	}

	return (r);
}

int	iscolliding(unsigned long long int a, unsigned long long int b)
{
	return (a & b);
}

void	fillit(t_list *tetri_list)
{
	unsigned long long int	grid;
	int	id;
	int	grid_size;
	t_tetriminos *tetri;

	grid = 0;
	grid_size = biggest_square(ft_lstsize(tetri_list) * 4);
	tetri = (t_tetriminos *)tetri_list->content;
	id = (int)tetri->pattern_id;
	grid += convert_to(g_mask_table[id][0], grid_size) << (grid_size * 0 + 1);
	/*
	** here lie's the bruteforce loop
	*/
	id = (int) ((t_tetriminos *)tetri_list->next->content)->pattern_id;
	if (iscolliding(grid, convert_to(g_mask_table[id][0], grid_size)))
		ft_putchar('@');

	print_grid(grid, grid_size);
}
