/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 17:05:24 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/16 19:12:00 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define DEBUG 0

#define OVERLAP(a, b) (a & b) != 0


void	print_grid(t_mask grid, t_mask bounds, int w)
{
	int		i;
	t_mask	a;

	(void) bounds;
	a = 1;
	i = 0;
	while (a)
	{
		if (bounds & a)
#if DEBUG == 1
			ft_putchar('@');
#else
		{
			i++;
			a = a << 1;
			continue ;
		}
		else if (a > grid)
			break ;
#endif
		else if (grid & a)
		{
			/*
			** TODO: replace # with tetri letter
			*/
			ft_putchar('#');

		}
		else
			ft_putchar('.');
			if (i > 0 && (i + 1) % w == 0)
				ft_putchar('\n');

		i++;
		a = a << 1;
	}
	//ft_putchar('\n');
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

t_mask	bruteforce(t_list *tetri_list, t_mask grid, size_t grid_size, t_mask bounds)
{
	t_tetrimino		*tetri;
	int				id;
	t_mask			shift;
	t_mask			tetri_mask;
	t_mask			shifted_tetri_mask;
	t_mask			forbidden_mask;
	t_mask			tmp;
	t_mask			tmp2;

	tmp2 = grid;
#if DEBUG == 1
	ft_putchar('@');
#endif
	tetri = (t_tetrimino *)tetri_list->content;
	id = (int)tetri->pattern_id;

	while (1)
	{
		grid = tmp2;
		tetri_mask = convert_to(g_mask_table[id][0], grid_size - 4);
		forbidden_mask = grid | bounds;
		shift = grid_size;
		shifted_tetri_mask = tetri_mask << shift;
		while (OVERLAP(forbidden_mask, shifted_tetri_mask))
		{
#if DEBUG == 1
			ft_putchar('_');
#endif
			shift = grid_size + grid_size * tetri->v_shift + tetri->h_shift;
			shifted_tetri_mask = tetri_mask << shift;
			
			tetri->h_shift++;
			if (tetri->h_shift > grid_size)
			{
				tetri->v_shift++;
				tetri->h_shift = 0;
				if (tetri->v_shift >= grid_size)
				{
#if DEBUG == 1
					ft_putchar('$');
#endif
					tetri->v_shift = 0;
					tetri->h_shift = 0;		
					return (0);
					//ft_putendl("grid too small");
					//error();
				}
			}
			// TODO: logic when grid size is 7
		}
		grid |= shifted_tetri_mask;
	
		if (tetri_list->next)
		{
			tmp = bruteforce(tetri_list->next, grid, grid_size, bounds);
			if (tmp == 0)
				continue ;
			grid = tmp;
		}
		break ;
	}

	return (grid);
}

void	fillit(t_list *tetri_list)
{
	t_mask		grid;
	t_mask		bounds;
	size_t		grid_size;
	size_t		i;

	grid = 0;
	bounds = 0;
	// + 1 for the bounds
	// Note: grids can be 7*7 max, so the biggest
	// number of tetriminos is 12 (perfect fit)
	// with a regular grid
	grid_size = biggest_square(ft_lstsize(tetri_list) * 4) + 1;
	
	i = -1;
	while (++i < grid_size * grid_size + grid_size)
		if (i < grid_size || i >= (grid_size * grid_size) || i % grid_size == 0)
			bounds += ullpow(2, i);

	//t_list	best_match; // A copy of the first best match
	grid = bruteforce(tetri_list, grid, grid_size, bounds);
	print_grid(grid, bounds, grid_size);
}
