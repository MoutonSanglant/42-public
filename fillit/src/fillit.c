/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 17:05:24 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/14 15:09:20 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define OVERLAP(a, b) a & b

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
			/*
			** TODO: replace # with tetri letter
			*/
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
		i++;
	}

	return (r);
}

void	fillit(t_list *tetri_list)
{
	unsigned long long int	grid;
	int		smallest_grid_size;

	grid = 0;
	smallest_grid_size = biggest_square(ft_lstsize(tetri_list) * 4);
	// ft_putendl("Here lies the bruteforce loop.");

	// Bruteforce rules:
	// Since the tests only check 7 letters max, it's pretty safe to use
	// a bruteforce algorithm without deep optimization. However, the
	// result should be find under 1 second max.
	// 1 - try to put letter in the grid,if there is no room left, extend
	// the grid
	// 1 - test with letter 1 in first position, if it is a perfect fill,
	// valid, else test with next letter in first position, until best fill
	// 2 - test with letter 2 in second position, 
	// 3 - 
	
	/*
	** t_tetriminos *tetri;
	** int	id;
	**
	** tetri = (t_tetriminos *)tetri_list->content;
	** id = (int)tetri->pattern_id;
	** grid += convert_to(g_mask_table[id][0], grid_size) << (grid_size * 0 + 1);
	** id = (int) ((t_tetriminos *)tetri_list->next->content)->pattern_id;
	** if (OVERLAP(grid, convert_to(g_mask_table[id][0], grid_size)))
	**		ft_putchar('@');
	*/

	print_grid(grid, smallest_grid_size);
}
