/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 17:15:49 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/08 01:01:12 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef LINUX
# include <stdio.h>
#endif
#include <errno.h>
#include "ft_ls.h"

void	error_unimplemented()
{
	ft_putendl("Unimplemented error");
	exit (1);
}

int		error_path(const char *s)
{
	ft_putstr("ft_ls: ");
	perror(s);
	return (1);
}

void	error_usage(int c)
{
	ft_printf("ft_ls: illegal option -- %c\nusage: ./ft_ls [-%s] [file ...]\n", c, VALID_FLAGS);
	exit(1);
}
