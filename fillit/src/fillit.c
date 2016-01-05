/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 17:05:24 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/05 18:10:47 by tdefresn         ###   ########.fr       */
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

static t_mask64 ullpow(int b, int e)
{
	if (e > 0)
		return (b * ullpow(b, e - 1));
	else
		return (1);
}

static t_bf_params	*init_bruteforce()
{
	t_bf_params	*p;

	p = (t_bf_params *)malloc(sizeof(t_bf_params));
	if (!p)
		error();
	p->list = ft_lstnew(NULL, 0);
	return(p);
}

static void	resize_masks(t_bf_params **p, size_t grid_size)
{
	size_t	i;

	(*p)->grid = (t_grid_mask *)malloc(sizeof(t_grid_mask));
	(*p)->grid->tetri = 0;
	(*p)->grid->right = 0;
	(*p)->grid->bottom = 0;
	(*p)->grid->fill = 0;
	i = 0;
	while (++i <= grid_size)
		(*p)->grid->right += ullpow(2, grid_size * i - 1);
	i = 0;
	while (i++ < grid_size )
		(*p)->grid->bottom += ullpow(2, grid_size * grid_size - grid_size + i);
	i = 0;
	while (i < grid_size * grid_size)
		(*p)->grid->fill += ullpow(2, i++);
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
	t_mask64			grid;
	size_t			grid_size;
	t_bf_params	*p;
	t_list			*list;

	grid = 0;
	grid_size = biggest_square(ft_lstsize(tetri_list) * 4);
	p = init_bruteforce();
	list = p->list;
	while (!grid)
	{
#if DEBUG == 1
		ft_putchar('!');
		ft_putnbr(grid_size);
#endif
		if (grid_size > 8)
			break ;
		ft_bzero(p->list, sizeof(t_mask64));
		resize_masks(&p, grid_size);
		grid = bruteforce(p, grid_size, tetri_list);
		if (grid == 0)
		{
			p->list = list;
			ft_lstdel(&p->list, &delelem);
			p->list = ft_lstnew(NULL, 0);
			//list = p->list;
			grid_size++;
		}
	}
#if DEBUG == 1
	ft_putchar('\n');
#endif
	if (!p->list)
		error();
	print_grid(grid_size, list);
	ft_lstdel(&p->list, &delelem);
	ft_memdel((void **)&p->grid);
	ft_memdel((void **)&p);
}
