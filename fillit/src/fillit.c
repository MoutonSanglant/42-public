/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 17:05:24 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/18 23:57:50 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	biggest_square(int n)
{
	int	i;

	i = 1;
	while (i * i < n)
		i++;
	return (i);
}

static t_mask ullpow(int b, int e)
{
	if (e > 0)
		return (b * ullpow(b, e - 1));
	else
		return (1);
}

static t_bruteforce_params	*init_bruteforce()
{
	t_bruteforce_params	*p;

	p = (t_bruteforce_params *)malloc(sizeof(t_bruteforce_params));
	if (!p)
		error();
	p->final_list = ft_lstnew(NULL, 0);
	return(p);
}

static void	resize_masks(t_bruteforce_params **p, size_t grid_size)
{
	size_t	i;

	(*p)->grid_mask = 0;
	(*p)->right_mask = 0;
	(*p)->bottom_mask = 0;
	(*p)->full_mask = 0;
	i = 0;
	while (++i <= grid_size)
		(*p)->right_mask += ullpow(2, grid_size * i - 1);
	i = 0;
	while (i++ < grid_size )
		(*p)->bottom_mask += ullpow(2, grid_size * grid_size - grid_size + i);
	i = 0;
	while (i < grid_size * grid_size)
		(*p)->full_mask += ullpow(2, i++);
}

void	delelem(void *content, size_t content_size)
{
	if (content)
	{
		ft_bzero(content, content_size);
		ft_memdel((void **)&content);
	}
}

void	fillit(t_list *tetri_list)
{
	t_mask			grid;
	size_t			grid_size;
	t_bruteforce_params	*p;
	t_list			*final_list;

	grid = 0;
	grid_size = biggest_square(ft_lstsize(tetri_list) * 4);
	p = init_bruteforce(tetri_list);
	final_list = p->final_list;
	while (!grid)
	{
#if DEBUG == 1
		ft_putchar('!');
		ft_putnbr(grid_size);
#endif
		if (grid_size > 8)
			break ;
		ft_bzero(p->final_list, sizeof(t_mask));
		resize_masks(&p, grid_size);
		grid = bruteforce(p, grid_size, tetri_list);
		if (grid == 0)
		{
			ft_lstdel(&p->final_list, &delelem);
			grid_size++;
		}
	}
#if DEBUG == 1
	ft_putchar('\n');
#endif
	if (!p->final_list)
		error();
	print_grid(grid_size, final_list);
	ft_lstdel(&p->final_list, &delelem);
	ft_memdel((void **)&p);
}
