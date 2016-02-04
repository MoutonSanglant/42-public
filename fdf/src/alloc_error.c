/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 15:05:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 15:26:54 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	alloc_error(char *error_obj, size_t alloc_size)
{
	ft_putstr("Memory allocation error: ");
	ft_putstr(error_obj);
	ft_putstr(" required a block of size ");
	ft_putnbr(alloc_size);
	ft_putendl(" but couldn't get it.'");
	exit(1);
}
