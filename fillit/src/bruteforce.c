/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruteforce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 20:48:20 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/18 23:57:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define OVERLAP(a, b) (a & b) != 0


/*
** Convert a 2-bytes pattern bitmask into a
** 8-bytes pattern bitmask, applying delta
*/
static t_mask	convert_to(unsigned short pattern_mask, int delta)
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

t_mask	bruteforce(t_bruteforce_params *p, size_t grid_size, t_list *tetri_list)
{
	t_tetrimino		*tetri;
	int				id;
	t_mask			shift;
	t_mask			tetri_mask;
	t_mask			shifted_tetri_mask;
	t_mask			tmp;
	t_mask			tmp2;

	// right & bottom mask
	t_mask			last_mask;
	t_list			*final_list;

	tmp2 = p->grid_mask;
	tetri = (t_tetrimino *)tetri_list->content;
	id = (int)tetri->pattern_id;

#if DEBUG == 1
	ft_putchar('@');
#endif
	shifted_tetri_mask = 0;
	p->final_list->content = malloc(sizeof(t_mask));
	if (p->final_list->content)
		p->final_list->content_size = sizeof(t_mask);
	while (1)
	{
		p->grid_mask = tmp2;
		tetri_mask = convert_to(g_mask_table[id][0], grid_size - 4);
		shift = grid_size * tetri->v_shift + tetri->h_shift;
		shifted_tetri_mask = tetri_mask << shift;
		if (p->final_list->content)
			p->final_list->content = ft_memcpy(p->final_list->content, (void const *)&(shifted_tetri_mask), sizeof(t_mask));
		last_mask = shifted_tetri_mask >> grid_size;

		while (1)
		{
			shift = grid_size * tetri->v_shift + tetri->h_shift;
			shifted_tetri_mask = tetri_mask << shift;
			if (shifted_tetri_mask > p->full_mask)
			{
				tetri->v_shift = 0;
				tetri->h_shift = 0;
				return (0);
			}
			if (OVERLAP(p->grid_mask, shifted_tetri_mask))
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
				last_mask = shifted_tetri_mask >> grid_size;
				if (OVERLAP(p->bottom_mask, last_mask) && OVERLAP(p->bottom_mask, shifted_tetri_mask))
				{
#if DEBUG == 1
					ft_putchar('&');
#endif
					tetri->v_shift = 0;
					tetri->h_shift = 0;
					return (0);
				}

				if (shift % grid_size)
				{
					last_mask = shifted_tetri_mask >> 1;
					if (OVERLAP(p->right_mask,last_mask) && OVERLAP(p->right_mask, shifted_tetri_mask))
					{
#if DEBUG == 1
						ft_putchar('=');
#endif
						tetri->h_shift = 0;
						tetri->v_shift++;
						continue ;
					}
				}
				if (p->final_list->content)
					p->final_list->content = ft_memcpy(p->final_list->content, (void const *)&(shifted_tetri_mask), sizeof(t_mask));

				tetri->h_shift++;
				break ;
			}
		}
		p->grid_mask |= shifted_tetri_mask;
		if (tetri_list->next)
		{
#if DEBUG == 1
			ft_putchar('/');
#endif
			final_list = p->final_list;
			p->final_list->next = ft_lstnew(NULL, 0);
			p->final_list = p->final_list->next;
			tmp = bruteforce(p, grid_size, tetri_list->next);
			if (tmp == 0)
			{
				p->final_list = final_list;
				ft_lstdel(&p->final_list->next, &delelem);
				continue ;
			}
			p->grid_mask = tmp;
		}
		break ;
	}

	return (p->grid_mask);

}

