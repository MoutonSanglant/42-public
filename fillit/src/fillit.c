/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 17:05:24 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/18 15:55:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define OVERLAP(a, b) (a & b) != 0

int		bit_in_list(t_mask bit, t_list *final_list, size_t list_size)
{
	size_t i;

	i = 0;
	while (i < list_size)
	{
		if (bit & *((t_mask *) ft_lstgetat(final_list, i)->content))
		{
			ft_putchar('A' + i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_grid(t_mask bounds, size_t w, t_list *final_list)
{

	
	t_mask	bit;
	size_t	list_size;
	size_t	i;

	list_size = ft_lstsize(final_list);
	bit = 1;
	i = 1;
	while (i <= w * w)
	{
#if DEBUG == 1
//		if (i > 0 && (i % w == 0))
//		{
//			ft_putchar('@');
//			ft_putchar('\n');
//		}
		if (bit & bounds)
		{
			ft_putchar('@');
	//		ft_putchar('\n');
	//		ft_putchar('@');
		}
		else if (bit_in_list(bit, final_list, list_size) == 0)
			ft_putchar('.');

		if (i > 0 && (i % (w) == 0))
			ft_putchar('\n');
#else
		if (i > w && (i <= w * w) && (i % w == 0))
			ft_putchar('\n');
		if (bit & bounds) {}
		else if (bit_in_list(bit, final_list, list_size) == 0)
			ft_putchar('.');

#endif
		//else if (bit > bounds)
		//	break ;

		bit <<= 1;
		i++;
	}
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
** Convert a 2-bytes pattern bitmask into a
** 8-bytes pattern bitmask, applying delta
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

void	dellist(void *content, size_t content_size)
{
	if (content)
	{
		ft_bzero(content, content_size);
		ft_memdel((void **)&content);
	}
}

#include <stdio.h>

t_mask	bruteforce(t_list *tetri_list, t_mask grid, size_t grid_size, t_list *final_list)
{
	t_tetrimino		*tetri;
	int				id;
	t_mask			shift;
	t_mask			tetri_mask;
	t_mask			shifted_tetri_mask;
	t_mask			tmp;
	t_mask			tmp2;

	// right & bottom mask
	t_mask			right_mask;
	t_mask			bottom_mask;
	t_mask		last_mask;
	size_t		i;

	right_mask = 0;
	bottom_mask = 0;
	i = 0; // skip the 0
	while (++i <= grid_size)
		right_mask += ullpow(2, grid_size * i - 1);

	i = 0;
	while (i++ < grid_size )
		bottom_mask += ullpow(2, grid_size * grid_size - grid_size + i);

	tmp2 = grid;
#if DEBUG == 1
	ft_putchar('@');
#endif
	tetri = (t_tetrimino *)tetri_list->content;
	id = (int)tetri->pattern_id;

	shifted_tetri_mask = 0;
	final_list->content = malloc(sizeof(t_mask));
	if (final_list->content)
		final_list->content_size = sizeof(t_mask);
	while (1)
	{
		grid = tmp2;
		tetri_mask = convert_to(g_mask_table[id][0], grid_size - 4);
		shift = grid_size * tetri->v_shift + tetri->h_shift;
		shifted_tetri_mask = tetri_mask << shift;
		if (final_list->content)
			final_list->content = ft_memcpy(final_list->content, (void const *)&(shifted_tetri_mask), sizeof(t_mask));
		
		while (1)
		{
			shift = grid_size * tetri->v_shift + tetri->h_shift;
			shifted_tetri_mask = tetri_mask << shift;

			if (OVERLAP(grid, shifted_tetri_mask))
			{
#if DEBUG == 1
				ft_putchar('_');
#endif
	
				tetri->h_shift++;
			}
			else
			{
				last_mask = shifted_tetri_mask >> grid_size;
				if (OVERLAP(bottom_mask, last_mask) && OVERLAP(bottom_mask, shifted_tetri_mask))
				{
#if DEBUG == 1
					ft_putchar('&');
#endif
					tetri->v_shift = 0;
					tetri->h_shift = 0;
					return (0);
				}
				last_mask = shifted_tetri_mask >> 1;
				if (OVERLAP(right_mask,last_mask) && OVERLAP(right_mask, shifted_tetri_mask))
				{
#if DEBUG == 1
					ft_putchar('=');
#endif
					tetri->h_shift = 0;
					tetri->v_shift++;
					//final_list->content = NULL;

					continue ;
				}
				if (final_list->content)
						final_list->content = ft_memcpy(final_list->content, (void const *)&(shifted_tetri_mask), sizeof(t_mask));

				tetri->h_shift++;
				break ;
			}
		}
		grid |= shifted_tetri_mask;
	
		if (tetri_list->next)
		{
			final_list->next = ft_lstnew(NULL, 0);
			tmp = bruteforce(tetri_list->next, grid, grid_size, final_list->next);
			if (tmp == 0)
			{
				ft_lstdel(&final_list->next, &dellist);
				continue ;
			}
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
	t_list		*final_list;
	t_mask		tmp;
	//t_list		*best_match;

	tmp = 0;
	grid = 0;
	bounds = 0;
	// + 1 for the bounds
	// Note: grids can be 7*7 max, so the biggest number
	// of tetriminos in a regular grid is 12 (perfect fit)
	//grid_size = biggest_square(ft_lstsize(tetri_list) * 4) + 1;
	grid_size = biggest_square(ft_lstsize(tetri_list) * 4);
	
	while (!tmp)
	{
		grid = 0;
		bounds = 0;
		i = -1;
		
#if DEBUG == 1
		ft_putchar('!');
		ft_putnbr(grid_size);
#endif
		if (grid_size > 8)
			break ;
		final_list = ft_lstnew(NULL, 0);
		tmp = bruteforce(tetri_list, grid, grid_size, final_list);
		if (tmp == 0)
		{
			ft_lstdel(&final_list, &dellist);
			grid_size++;
		}
	}
#if DEBUG == 1
	ft_putchar('\n');
#endif
	if (!final_list)
		error();

	print_grid(0, grid_size, final_list);
}
