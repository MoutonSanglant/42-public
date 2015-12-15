/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 17:05:24 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/15 12:45:45 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define OVERLAP(a, b) (a & b) != 0

void	print_grid(unsigned long long int grid, unsigned long long int bounds, int w)
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
			//if (i / w >= w)
			//	break;
		}

		if (bounds & a)
			ft_putchar('@');
		else if (grid & a)
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

/*
** Convert the 4*4 bits value of the pattern to a
** n*n bits value. Be aware of the bound !
*/
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

unsigned long long int ullpow(int b, int e)
{
	if (e > 0)
		return (b * ullpow(b, e - 1));
	else
		return (1);
}
#include <stdio.h>
void	fillit(t_list *tetri_list)
{
	unsigned long long int	grid;
	unsigned long long int	bounds;
	size_t		grid_size;
	size_t		i;

	grid = 0;
	bounds = 0;
	// + 1 for the bounds
	// Remember: a grid can't be bigger than 7*7, so the biggest
	// number of tetriminos is 12 with a regular grid, but we could use
	// a splitted grid for bigger number of tetriminos
	//grid_size = biggest_square(ft_lstsize(tetri_list) * 4) + 1;
	grid_size = 7 + 1;

	i = -1;
	while (++i <= grid_size * grid_size + grid_size)
		if (i < grid_size || i >= (grid_size * grid_size) || i % grid_size == 0)
			bounds += ullpow(2, i);

	// ft_putendl("Here lies the bruteforce loop.");

	// Problem 1:
	// - the tetrimino is out of bound
	// - since we never ask it to be out of bound it should be fine

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

	t_tetriminos *tetri;
	int	id;

	tetri = (t_tetriminos *)tetri_list->content;
	id = (int)tetri->pattern_id;
	

	unsigned long long int shift;
	unsigned long long int tetri_mask;
	unsigned long long int shifted_tetri_mask;

	size_t a;
	size_t b;

	a = -1;
	b = 0;
	i = 0;
	// Count how many tetrimino can be suited in the grid
	while (b < grid_size)
	{
		a++;
		shift = grid_size + grid_size * b + a;
		tetri_mask = convert_to(g_mask_table[id][0], grid_size);
		shifted_tetri_mask = tetri_mask << shift;
		// Check whether the tetrimino is out of bound when there there is no
		// bottom bound, it happens when the grid size is 7x7
		if (grid_size > 7)
		{
			if (tetri_mask != shifted_tetri_mask >> shift)
				continue ;
		}
		if (!OVERLAP(bounds, shifted_tetri_mask))
		{
			//grid += shifted_tetri_mask;
			grid |= shifted_tetri_mask;
			i++;
		}
		if (a >= grid_size)
		{
			b++;
			a = -1;
		}
		//id = (int) ((t_tetriminos *)tetri_list->next->content)->pattern_id;
	}

	ft_putstr("Avaible positions for this terimino: ");
	ft_putnbr(i);
	ft_putchar('\n');
	
	//if (OVERLAP(grid, convert_to(g_mask_table[id][0], grid_size)))
	//	ft_putchar('@');

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

	print_grid(grid, bounds, grid_size);
}
