/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 19:56:02 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/18 23:51:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		bit_in_list(t_mask bit, t_list *final_list, size_t list_size)
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

void	print_grid(size_t w, t_list *final_list)
{	
	t_mask	bit;
	size_t	list_size;
	size_t	i;

	i = 1;
	bit = 1;
	list_size = ft_lstsize(final_list);
	while (i <= w * w)
	{
		if (bit_in_list(bit, final_list, list_size) == 0)
			ft_putchar('.');
		if (i > 0 && (i % (w) == 0))
			ft_putchar('\n');
		bit <<= 1;
		i++;
	}
}
