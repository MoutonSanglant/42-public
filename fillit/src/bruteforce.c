/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruteforce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 20:48:20 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/19 13:19:54 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define OVERLAP(a, b) (a & b) != 0


/*
** Convert a 2-bytes pattern bitmask into a
** 8-bytes pattern bitmask, applying delta
*/
static t_mask64	convert_to(t_mask16 pattern_mask, int delta)
{
	t_mask64 mask;
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
			mask |= (pattern_mask & (1 << bitshift++)) << lineshift;
		}
	}
	else
	{
		while (bitshift < 16)
		{
			if (bitshift > 0 && bitshift % 4 == 0)
				lineshift -= delta;
			mask |= (pattern_mask & (1 << bitshift++)) >> lineshift;
		}
	}
	return (mask);
}

static int	overlap_test(t_tetri_masks *tetri_masks, t_bf_params *p, t_tetrimino *tetri, size_t grid_size)
{
	while (1)
	{
		tetri_masks->shift = grid_size * tetri->v_shift + tetri->h_shift;
		tetri_masks->shifted = tetri_masks->tetri << tetri_masks->shift;
		if (tetri_masks->shifted > p->grid->fill)
		{
			tetri->v_shift = 0;
			tetri->h_shift = 0;
			return (1);
		}
		if (OVERLAP(p->grid->tetri, tetri_masks->shifted))
		{
#if DEBUG == 1
			ft_putchar('.');
#endif	
			tetri->h_shift++;
		}
		else
		{
#if DEBUG == 1
			ft_putchar('<');
#endif	
			tetri_masks->last = tetri_masks->shifted >> grid_size;
			if (OVERLAP(p->grid->bottom, tetri_masks->last) && OVERLAP(p->grid->bottom, tetri_masks->shifted))
			{
#if DEBUG == 1
				ft_putchar('&');
#endif
				tetri->v_shift = 0;
				tetri->h_shift = 0;
				return (1);
			}
			else if (tetri_masks->shift % grid_size)
			{
				tetri_masks->last = tetri_masks->shifted >> 1;
				if (OVERLAP(p->grid->right, tetri_masks->last) && OVERLAP(p->grid->right, tetri_masks->shifted))
				{
#if DEBUG == 1
					ft_putchar('=');
#endif
					tetri->h_shift = 0;
					tetri->v_shift++;
					continue ;
				}
			}
		if (p->result_list->content)
			p->result_list->content = ft_memcpy(p->result_list->content, (void const *)&(tetri_masks->shifted), sizeof(t_mask64));
			tetri->h_shift++;
			break ;
		}
	}
	return (0);
}

char	tetri_enter_grid(t_bf_params *p, size_t grid_size, t_list *tetri_list)
{
	t_list		*previous_list;

#if DEBUG == 1
	ft_putchar('/');
#endif
	previous_list = p->result_list;
	p->result_list->next = ft_lstnew(NULL, 0);
	p->result_list = p->result_list->next;
	p->grid->tetri = bruteforce(p, grid_size, tetri_list->next);
	if (p->grid->tetri == 0)
	{
		p->result_list = previous_list;
		ft_lstdel(&p->result_list->next, &delelem);
		return (0);
	}
	return (1);
}

t_mask64	bruteforce(t_bf_params *p, size_t grid_size, t_list *tetri_list)
{
	t_tetrimino	*tetri;
	t_tetri_masks	tetri_masks;
	t_mask64	last_grid_mask;

	last_grid_mask = p->grid->tetri;
	tetri = (t_tetrimino *)tetri_list->content;
#if DEBUG == 1
	ft_putchar('@');
#endif
	tetri_masks.shifted = 0;
	p->result_list->content = malloc(sizeof(t_mask64));
	if (p->result_list->content)
		p->result_list->content_size = sizeof(t_mask64);
	tetri_masks.tetri = convert_to(g_mask_table[(int)tetri->pattern_id][0], grid_size - 4);
	while (1)
	{
		p->grid->tetri = last_grid_mask;
		if (overlap_test(&tetri_masks, p, tetri, grid_size))
			return (0);
		p->grid->tetri |= tetri_masks.shifted;
		if (tetri_list->next && !tetri_enter_grid(p, grid_size, tetri_list))
			continue ;
		break ;
	}
	return (p->grid->tetri);
}
