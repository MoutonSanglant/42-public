/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuchwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 10:51:42 by mabuchwa          #+#    #+#             */
/*   Updated: 2016/01/10 02:31:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int		ft_check_tetri(char *buf, int i)
{
	int		c;

	c = 0;
	if (buf[4] != '\n' || buf[9] != '\n' || buf[14] != '\n' || buf[19] != '\n')
		return (-1);
	if (buf[0] != '.' && buf[0] != '#')
		return (-1);
	if (buf[i] != '.' && buf[i] != '#' && buf[i] != '\n')
			return (-1);
	if (buf[i] == '#' && buf[i + 1] != '#' && buf[i - 1] != '#'
			&& buf[i + 5] != '#' && buf[i - 5] != '#')
		return (-1);
	if (buf[i] == '#' && (i + 1) < 21 && buf[i + 1] == '#')
		c++;
	if (buf[i] == '#' && (i - 1) > 0 && buf[i - 1] == '#')
		c++;
	if (buf[i] == '#' && (i + 5) < 21 && buf[i + 5] == '#')
		c++;
	if (buf[i] == '#' && (i - 5) > 0 && buf[i - 5] == '#')
		c++;
	return (c);
}

int				ft_check_file(char *buf, int i, int nl)
{
	int		piece;
	int		c;

	piece = 0;
	c = 0;
	while (buf[i])
	{
		if (buf[i] == '#')
			piece++;
		if (ft_check_tetri(buf, i) >= 0)
		{
			if (ft_check_tetri(buf, i) > c && buf[i] == '#')
				c = ft_check_tetri(buf, i);
		}
		else
			return (1);
		if (buf[i] == '\n')
			nl++;
		i++;
	}
	if (c < 2)
		return (1);
	if ((i == 21 && nl != 5) || piece != 4)
		return (1);
	return (0);
}
