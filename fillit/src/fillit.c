/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 17:05:24 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/16 13:41:56 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define OVERLAP(a, b) (a & b) != 0

void	print_grid(t_mask grid, t_mask bounds, int w)
{
	int i;
	t_mask a;

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

	i = 1;
	while (i * i < n)
		i++;

	return (i);
}

/*
** Convert a 16bit pattern bitmask to a 64bit pattern bitmask
** applying a delta
*/
t_mask	convert_to(unsigned short pattern_mask, int delta)
{
	t_mask mask;
	size_t bitshift;
	size_t lineshift;

	mask = 0;
	bitshift = 0;
	lineshift = 0;
	if (delta > 0)
	{
		while (bitshift < 16)
		{
			if (bitshift > 0 && bitshift % 4 == 0)
				lineshift += delta;
			mask |= (pattern_mask & (1 << bitshift)) << lineshift;
			bitshift++;
		}
	}
	else
	{
		while (bitshift < 16)
		{
			if (bitshift > 0 && bitshift % 4 == 0)
				lineshift -= delta;
			mask |= (pattern_mask & (1 << bitshift)) >> lineshift;
			bitshift++;
		}
	}
	return (mask);
}

t_mask ullpow(int b, int e)
{
	if (e > 0)
		return (b * ullpow(b, e - 1));
	else
		return (1);
}
#include <stdio.h>
void	fillit(t_list *tetri_list)
{
	t_mask	grid;
	t_mask	bounds;
	t_mask	forbidden_mask;
	size_t		grid_size;
	size_t		i;

	grid = 0;
	bounds = 0;
	// + 1 for the bounds
	// Remember: a grid can't be bigger than 7*7, so the biggest
	// number of tetriminos is 12 with a regular grid, but we could use
	// a splitted grid for bigger number of tetriminos
	grid_size = biggest_square(ft_lstsize(tetri_list) * 4) + 1;
	//grid_size += 2;
	
	i = -1;
	while (++i < grid_size * grid_size + grid_size)
		if (i < grid_size || i >= (grid_size * grid_size) || i % grid_size == 0)
			bounds += ullpow(2, i);

	t_tetriminos *tetri;
	int	id;

	t_mask shift;
	t_mask tetri_mask;
	t_mask shifted_tetri_mask;

	//t_list	best_match; // A copy of the first best match

	tetri = (t_tetriminos *)tetri_list->content;
	id = (int)tetri->pattern_id;
	//id = (int)tetri->pattern_id + 4;

	
	while (1)
	{
		tetri_mask = convert_to(g_mask_table[id][0], grid_size - 4);
		forbidden_mask = grid | bounds;
		while (OVERLAP(forbidden_mask, shifted_tetri_mask))
		{
			shift = grid_size + grid_size * tetri->v_shift + tetri->h_shift;
			shifted_tetri_mask = tetri_mask << shift;
			
			tetri->h_shift++;
			if (tetri->h_shift > grid_size)
			{
				tetri->v_shift++;
				tetri->h_shift = 0;
				if (tetri->v_shift >= grid_size)
				{
					ft_putendl("grid too small");
					error();
				}
			}
		
			// TODO: logic when grid size is 7
			
		}
		grid |= shifted_tetri_mask;
		//grid |= tetri_mask;
		break;
	}
	

	/*
	size_t a = -1;
	size_t b = 0;
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
	*/	
	print_grid(grid, bounds, grid_size);
	//print_grid(grid, 0, grid_size);
}
