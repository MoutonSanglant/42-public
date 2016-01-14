/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colle02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/06 22:04:01 by tdefresn          #+#    #+#             */
/*   Updated: 2015/09/06 22:04:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	ft_draw_square(int x, int y, int i, int j)
{
	if (i == 1 && j == 1)
		ft_putchar('A');
	else if (j > 1 && j < x && i == 1)
		ft_putchar('B');
	else if (j == x && i == 1)
		ft_putchar('A');
	else if (i > 1 && i < y && !(j > 1 && j < x))
		ft_putchar('B');
	else if (i > 1 && i < y && (j > 1 || j < x))
		ft_putchar(' ');
	else if (j == 1 && i == y)
		ft_putchar('C');
	else if (j > 1 && j < x && i == y)
		ft_putchar('B');
	else if (j == x && i == y)
		ft_putchar('C');
	if (j == x)
		ft_putchar('\n');
}

void	colle(int x, int y)
{
	int i;
	int j;

	i = 1;
	j = 1;
	while (i <= y)
	{
		while (j <= x)
		{
			ft_draw_square(x, y, i, j);
			j++;
		}
		j = 1;
		i++;
	}
}
