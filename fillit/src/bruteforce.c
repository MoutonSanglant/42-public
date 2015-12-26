/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruteforce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 20:48:20 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/26 20:47:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define OVERLAP(a, b) (a & b) != 0

/*
** Convert a 2-bytes pattern bitmask into a
** 8-bytes pattern bitmask, applying delta
*/
static t_mask64	convert(t_mask16 pattern_mask, int delta)
{
	t_mask64	mask;
	size_t		bitshift;
	size_t		lineshift;

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

static int	valid_position(t_bf_params *p, size_t grid_size,
							t_tetrimino *tetri, t_tetri_masks *tetri_masks)
{
	tetri_masks->last = tetri_masks->shifted >> grid_size;
	if (OVERLAP(p->grid->bottom, tetri_masks->last)
			&& OVERLAP(p->grid->bottom, tetri_masks->shifted))
	{
		tetri->h_shift = 0;
		tetri->v_shift = 0;
		return (1);
	}
	else if (tetri_masks->shift % grid_size)
	{
		tetri_masks->last = tetri_masks->shifted >> 1;
		if (OVERLAP(p->grid->right, tetri_masks->last)
				&& OVERLAP(p->grid->right, tetri_masks->shifted))
		{
			tetri->h_shift = 0;
			tetri->v_shift++;
			return (1);
		}
	}
	p->list->content = ft_memcpy(p->list->content, &tetri_masks->shifted,
									sizeof(t_mask64));
	tetri->h_shift++;
	return (0);
}

static int	overlap_test(t_bf_params *p, size_t grid_size,
							t_tetrimino *tetri, t_tetri_masks *tetri_masks)
{
	while (1)
	{
		tetri_masks->shift = grid_size * tetri->v_shift + tetri->h_shift;
		tetri_masks->shifted = tetri_masks->tetri << tetri_masks->shift;
		if (tetri_masks->shifted > p->grid->fill)
		{
			tetri->h_shift = 0;
			tetri->v_shift = 0;
			return (1);
		}
		if (OVERLAP(p->grid->tetri, tetri_masks->shifted))
			tetri->h_shift++;
		else if (!valid_position(p, grid_size, tetri, tetri_masks))
			break ;
	}
	return (0);
}

static int	bruteforce_tetri(t_bf_params *p, size_t grid_size,
								t_list *tetri_list)
{
	t_list		*previous_list;

#if DEBUG == 1
	ft_putchar('/');
#endif
	previous_list = p->list;
	/*
	** TODO
	** MALLOC: p_rl_n01
	** >> free attribued in bruteforce_tetri (line 10) <<
	** >> memerror behaviour: call error() <<
	*/
	p->list->next = ft_lstnew(NULL, 0);
	if (!p->list->next)
		error();
	p->list = p->list->next;
	p->grid->tetri = bruteforce(p, grid_size, tetri_list->next);
	if (p->grid->tetri == 0)
	{
		p->list = previous_list;
		ft_lstdel(&p->list->next, &delelem);
		return (1);
	}
	return (0);
}

t_mask64	bruteforce(t_bf_params *p, size_t grid_size, t_list *tetri_list)
{
	t_tetrimino		*tetri;
	t_mask64		previous_grid_mask;
	t_tetri_masks	tetri_masks;

#if DEBUG == 1
	ft_putchar('@');
#endif
	/*
	** TODO
	** MALLOC: p_rl_c01
	** >> No free attribued <<
	** >> memerror behaviour: call error() <<
	*/
	p->list->content = malloc(sizeof(t_mask64));
	if (!p->list->content)
		error();
	p->list->content_size = sizeof(t_mask64);
	tetri = (t_tetrimino *)tetri_list->content;
	tetri_masks.shifted = 0;
	tetri_masks.tetri = convert(g_mask_table[(int)tetri->pattern_id][0],
								grid_size - 4);
	previous_grid_mask = p->grid->tetri;
	while (1)
	{
		p->grid->tetri = previous_grid_mask;
		if (overlap_test(p, grid_size, tetri, &tetri_masks))
			return (0);
		p->grid->tetri |= tetri_masks.shifted;
		if (tetri_list->next && bruteforce_tetri(p, grid_size, tetri_list))
			continue ;
		break ;
	}
	return (p->grid->tetri);
}
