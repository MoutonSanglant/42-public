/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 17:15:49 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/13 10:53:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef LINUX
# include <stdio.h>
#endif
#include <errno.h>
#include "ft_ls.h"

void	error_unimplemented(void)
{
	ft_putendl_fd("Unimplemented error", 2);
	exit(1);
}

int		error_path(const char *s)
{
	char	*str;

	str = ft_strjoin("ft_ls: ", s);
	perror(s);
	ft_strdel(&str);
	return (1);
}

void	error_usage(int c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ft_ls [", 2);
	ft_putstr_fd(VALID_FLAGS, 2);
	ft_putendl_fd("] [file ...]", 2);
	exit(1);
}
